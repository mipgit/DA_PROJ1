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
        string key, value, value2, maxWalk;

        getline(ss, key, ':');  // por exemplo, "Mode:"
        getline(ss, value);     // por exemplo, "driving"

        // tiramos espaços
        while (!value.empty() && value.front() == ' ') {
            value.erase(0, 1);
        }

        if (key == "Mode" && value == "driving") mode = value;
        else if (key == "Source" && stoi(value) > 0) source = stoi(value);
        else if (key == "Destination" && stoi(value) > 0) dest = stoi(value);
        else if (key == "MaxWalkTime" && stoi(value) > 0) maxWalk = stoi(value);
        else if (key == "AvoidNodes") {
            stringstream nodes(value);
            string node;
            while (getline(nodes, node, ',')) {
                avoidNodes.push_back(stoi(node));
            }
        }
        else if (key == "AvoidSegments") {
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
                    if (src > 0 && dst > 0) {
                        avoidSegs.push_back(make_pair(src, dst));
                    }
                }
            }
        }
        
        else {
            cout << "Invalid input format in " << filename << "\n\n";
            return false;
        }
    }

    inFile.close();
    return true;
}

/*
void RestrictedRoute::writeToFile(ostream &outFile) {

    outFile << "Source:" << source << "\n";
    outFile << "Destination:" << dest << "\n";
    
    //best
    outFile << "BestDrivingRoute:";

    if (bestRoute.empty()) {
        outFile << "none\n";
    } else {
        for (size_t i = 0; i < bestRoute.size(); i++) {
            outFile << bestRoute[i];
            if (i < bestRoute.size() - 1) outFile << ",";
        }
        outFile << "(" << bestTime << ")\n";
    }


    //best
    outFile << "AlternativeDrivingRoute:";

    if (altRoute.empty()) {
        outFile << "none\n";
    } else {
        for (size_t i = 0; i < altRoute.size(); i++) {
            outFile << altRoute[i];
            if (i < altRoute.size() - 1) outFile << ",";
        }
        outFile << "(" << altTime << ")\n";
    }

}

*/







void RestrictedRoute::calculateRoute() {
    
    Graph<Location>* copy = copyGraph(cityMap);

    for (auto id : avoidNodes) {
        Vertex<Location>* loc = copy->findLocationId(id);
        if(loc) copy->removeVertex(loc->getInfo());     // if it isn't nullptr
    }

    for (auto p : avoidSegs) {
        int sId = p.first;
        int dId = p.second;

        Vertex<Location>* source = copy->findLocationId(sId);
        Vertex<Location>* dest = copy->findLocationId(dId);

        source->removeEdge(dest->getInfo());
    }

    
    dijkstra(copy, source, node);
    route = getPath(copy, source, node);

    dijkstra(copy, node, dest);
    route2 = getPath(copy, source, node);

    route.insert(route.end(), route2.begin(), route2.end());

    Vertex<Location> *destVertex = copy->findLocationId(dest);
    time = destVertex->getDist();


    //avoid mem leak
    delete copy;
}





void RestrictedRoute::processRoute(ostream &outFile) {
    calculateRoute();
    writeToFile(outFile);    
}