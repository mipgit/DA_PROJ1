#include <iostream>
#include "RestrictedRoute.h"

using namespace std;


//É PRECISO FAZER A CONFIRMAÇÃO SE O SOURCE/DEST SÃO IDS VÁLIDOS
//E CASO O USER NAO COLOQUE NADA, DAR MENSAGEM DE ERRO

bool RestrictedRoute::readFromFile(const string &filename) {
    
    ifstream inFile(filename);

    if (!inFile ) {
        cout << "\nError opening files.\n";
        return false;
    }

    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string key, value, value2;

        getline(ss, key, ':');  // por exemplo, "Mode:"
        getline(ss, value);     // por exemplo, "driving"

        // tiramos espaços
        while (!value.empty() && value.front() == ' ') {
            value.erase(0, 1);
        }

        if (key == "Mode" && value == "driving") mode = value;
        else if (key == "Source" && stoi(value) > 0) source = stoi(value);
        else if (key == "Destination" && stoi(value) > 0) dest = stoi(value);
        else if (key == "AvoidNodes") {
            if (!value.empty()) {
                stringstream nodes(value);
                string node;
                while (getline(nodes, node, ',')) {
                    if(!node.empty()) avoidNodes.push_back(stoi(node));
                }
            }

        }
        else if (key == "AvoidSegments") {
            if (!value.empty()) {
                stringstream segs(value);
                string seg;
                while (getline(segs, seg, ')')) {
                    if (!seg.empty()) {
                        stringstream pairStream(seg);
                        int src, dst;
                        pairStream.ignore(); 
                        pairStream >> src;
                        pairStream.ignore(); 
                        pairStream >> dst;
                        if (src > 0 && dst > 0) avoidSegs.push_back(make_pair(src, dst));
                    }
                }
            }
        }
        
        else if (key == "IncludeNode") {  
            if (!value.empty()) node = stoi(value);
            else node = -1;  
        }

        else {
            cout << "\nInvalid input format in " << filename << "\n";
            return false;
        }
    }

    inFile.close();
    return true;
}


void RestrictedRoute::writeToFile(ostream &outFile) {

    outFile << "Source:" << source << "\n";
    outFile << "Destination:" << dest << "\n";
    
    outFile << "RestrictedDrivingRoute:";

    if (route.empty()) {
        outFile << "none\n";
    } else {
        for (size_t i = 0; i < route.size(); i++) {
            outFile << route[i];
            if (i < route.size() - 1) outFile << ",";
        }
        outFile << "(" << time << ")\n";
    }

}




void RestrictedRoute::calculateRoute() {
    
    Graph<Location>* copy = copyGraph(cityMap);

    if (!avoidNodes.empty()) {
        for (auto id : avoidNodes) {
            Vertex<Location>* loc = copy->findLocationId(id);
            if(loc) copy->removeVertex(loc->getInfo());     // if it isn't nullptr
        }
    }


    if (!avoidSegs.empty()) {
        for (auto p : avoidSegs) {
            int sId = p.first;
            int dId = p.second;
    
            Vertex<Location>* source = copy->findLocationId(sId);
            Vertex<Location>* dest = copy->findLocationId(dId);
    
            if(source!=nullptr && dest!=nullptr) source->removeEdge(dest->getInfo());
        }
    }


    if (node!=-1 && node!=source && node!=dest) {

        //path from source to mandatory node
        dijkstra(copy, source, node);
        route = getPath(copy, source, node);
        Vertex<Location> *nodeVertex = copy->findLocationId(node);
        int time1 = nodeVertex->getDist();
        
        //path from mandatory node to destination
        dijkstra(copy, node, dest);
        vector<int> route2 = getPath(copy, node, dest);
        Vertex<Location> *destVertex = copy->findLocationId(dest);
        int time2 = destVertex->getDist();

        //combination of the two results
        route.insert(route.end(), route2.begin()+1, route2.end());  
        time = time1 + time2;

    } else {
        dijkstra(copy, source, dest);
        route = getPath(copy, source, dest);
        Vertex<Location> *destVertex = copy->findLocationId(dest);
        time = destVertex->getDist();
    }


    //avoid mem leak
    delete copy;
}





void RestrictedRoute::processRoute(ostream &outFile) {
    calculateRoute();
    writeToFile(outFile);    
}