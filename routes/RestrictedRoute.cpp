#include <iostream>
#include "RestrictedRoute.h"

using namespace std;


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

        getline(ss, key, ':');
        getline(ss, value);

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
                    if(!node.empty()) {
                        int id = stoi(node);
                        if (id == source || id == dest) cout << "Can't avoid source/dest nodes!\n";
                        else avoidNodes.push_back(id);
                    }
                }
            }
        }

        else if (key == "AvoidSegments") {
            if (!value.empty()) {
                stringstream segs(value);
                string seg;

                while (getline(segs, seg, ')')) { 

                    //the segment itself
                    if (!seg.empty()) {

                        // "(src,dest" -> "src,dest"
                        seg.erase(remove(seg.begin(), seg.end(), '('), seg.end());

                        stringstream pairNodes(seg);
                        int src, dst;
                        char comma;
            
                        // we extract src and dest
                        if (pairNodes >> src >> comma >> dst && comma == ',') {
                            if (src > 0 && dst > 0) avoidSegs.push_back(make_pair(src, dst));
                        }
                    }


                    //the comma separating segments
                    char separator;
                    segs >> separator; 
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

    if (cityMap->findLocationId(source) == nullptr) outFile << "Invalid source id! Please enter a node id present in the graph.\n";
    else outFile << "Source:" << source << "\n";

    if (cityMap->findLocationId(dest) == nullptr) outFile << "Invalid destination id! Please enter a node id present in the graph.\n";
    else outFile << "Destination:" << dest << "\n";
    
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

    copy->avoidVertices(avoidNodes);
    copy->avoidEdges(avoidSegs);

    if (node!=-1 && node!=source && node!=dest) {

        //path from source to mandatory node
        if (initDijkstra(copy)) dijkstra(copy, source, node, 1);
        route = getPath(copy, source, node);
        Vertex<Location> *nodeVertex = copy->findLocationId(node);
        int time1 = nodeVertex->getDist();

        //avoid repetition of nodes
        route.pop_back();
        copy->avoidVertices(route);
        
        //path from mandatory node to destination
        if (initDijkstra(copy)) dijkstra(copy, node, dest, 1);
        vector<int> route2 = getPath(copy, node, dest);
        Vertex<Location> *destVertex = copy->findLocationId(dest);
        int time2 = destVertex->getDist();

        //combination of the two results
        route.insert(route.end(), route2.begin(), route2.end());  
        time = time1 + time2;

    } else {
        if (initDijkstra(copy)) dijkstra(copy, source, dest, 1);
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