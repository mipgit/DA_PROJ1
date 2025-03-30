#include <iostream>
#include "EcoRoute.h"

using namespace std;


vector<int> EcoRoute::findParking(int source, int dest) {
    vector<int> parkingNodes;
    for (auto vertex : cityMap->getVertexSet()) {
        Location loc = vertex->getInfo();
        if (loc.hasParking() && loc.getId() != source && loc.getId() != dest) {
            parkingNodes.push_back(vertex->getInfo().getId());
        }
    }
    return parkingNodes;
}



bool EcoRoute::readFromFile(const string &filename) {
    
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

        if (key == "Mode" && value == "driving-walking") {mode = value;}
        else if (key == "Source" && stoi(value) > 0) {source = stoi(value);}
        else if (key == "Destination" && stoi(value) > 0) {dest = stoi(value);}
        else if (key == "MaxWalkTime" && stoi(value) > 0) {maxWalk = stoi(value);}

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
        
        else {
            cout << "Invalid input format in " << filename << "\n\n";
            return false;
        }
    }

    inFile.close();
    return true;
}


void EcoRoute::writeToFile(ostream &outFile) {

    if (cityMap->findLocationId(source) == nullptr) outFile << "Invalid source id! Please enter a node id present in the graph.\n";
    else outFile << "Source:" << source << "\n";

    if (cityMap->findLocationId(dest) == nullptr) outFile << "Invalid destination id! Please enter a node id present in the graph.\n";
    else outFile << "Destination:" << dest << "\n";
    
    outFile << "DrivingRoute:";
    if (drivingRoute.empty()) {
        outFile << "none\n";
    } else {
        
        for (size_t i = 0; i < drivingRoute.size(); i++) {
            outFile << drivingRoute[i];
            if (i < drivingRoute.size() - 1) outFile << ",";
        }
        outFile << "(" << drivingTime << ")\n";
    }

    outFile << "ParkingNode:";
    if (parkingNode == -1) outFile << "none\n";
    else outFile << parkingNode << "\n";
    
    
    outFile << "WalkingRoute:";
    if (walkingRoute.empty()) {
        outFile << "none\n";
    } else {
        for (size_t i = 0; i < walkingRoute.size(); i++) {
            outFile << walkingRoute[i];
            if (i < walkingRoute.size() - 1) outFile << ",";
        }
        outFile << "(" << walkingTime << ")\n";
    }

    outFile << "TotalTime:";
    if (time == 0) outFile << "\n";
    else outFile << time;


    if (message!="") {
        outFile << "Message:" << message;
    }
}




bool EcoRoute::calculateRoute() {
    
    Graph<Location>* copy = copyGraph(cityMap);

    copy->avoidVertices(avoidNodes);
    copy->avoidEdges(avoidSegs);

    int minTotalTime = numeric_limits<int>::max();
    bool validRoute = false;
    string failureReason = "No possible routes.\n";

    // finds all parking nodes
    vector<int> parkingNodes = findParking(source, dest);

    if (parkingNodes.empty()) failureReason = "No available parking nodes.\n";


    for (int parking : parkingNodes) {

        if (initDijkstra(copy)) dijkstra(copy, source, parking, 1);
        vector<int> drivingPath = getPath(copy, source, parking);
        if (drivingPath.empty()) continue; 

        int dt = copy->findLocationId(parking)->getDist();

        if (initDijkstra(copy)) {
            for (int i = 0; i < drivingPath.size()-1; i++) {
                Vertex<Location> *p = copy->findLocationId(drivingPath[i]);
                p->setVisited(true);
            }
            
            dijkstra(copy, parking, dest, 0);
        }

        vector<int> walkingPath = getPath(copy, parking, dest);
        if (walkingPath.empty()) continue; 

        int wt = copy->findLocationId(dest)->getDist();

        int totalTime = dt + wt;

        if (wt > maxWalk) {
            failureReason = "No possible route with max. walking time of " + to_string(maxWalk) + " minutes.\n";
            AproxSolution sol = {drivingPath, dt, parking, walkingPath, wt, totalTime};
            aproxSolutions.push_back(sol);
            continue;
        } 

        if (totalTime < minTotalTime || (totalTime == minTotalTime && wt > walkingTime)) {
            validRoute = true;
            
            minTotalTime = totalTime;
            time = totalTime;
            drivingTime = dt;
            walkingTime = wt;

            parkingNode = parking;
            drivingRoute = drivingPath;
            walkingRoute = walkingPath;
        }
    }

    delete copy; //we free mem

    if (!validRoute) {
        message = failureReason;
        return false;
    }
    return true;
}


void EcoRoute::calculateAproxSolution(ostream &outFile) {

    if (aproxSolutions.empty()) {
        outFile << "\nThere are no approximate solutions for your input.";
        return;
    }

    outFile << "\nApproximate solution(s) for your input:\n\n";

    outFile << "Source:" << source << "\n";
    outFile << "Destination:" << dest << "\n";

    //we sort the solutions by best total time
    sort(aproxSolutions.begin(), aproxSolutions.end(), 
              [](const AproxSolution& a, const AproxSolution& b) {
                  return a.time < b.time;
              }
        );

    //we only process the first 2 solutions w/ best time
    for (size_t i = 0; i < min(aproxSolutions.size(), size_t(2)); i++) {

        AproxSolution cur = aproxSolutions[i];

        outFile << "DrivingRoute" << i+1 << ":";

        if (cur.drivingRoute.empty()) {
            outFile << "none\n";
        } else {
            
            for (size_t i = 0; i < cur.drivingRoute.size(); i++) {
                outFile << cur.drivingRoute[i];
                if (i < cur.drivingRoute.size() - 1) outFile << ",";
            }
            outFile << "(" << cur.drivingTime << ")\n";
        }
    
        outFile << "ParkingNode" << i+1 << ":";
        if (cur.parkingNode == -1) outFile << "none\n";
        else outFile << cur.parkingNode << "\n";
        
        
        outFile << "WalkingRoute" << i+1 << ":";
    
        if (cur.walkingRoute.empty()) {
            outFile << "none\n";
        } else {
            
            for (size_t i = 0; i < cur.walkingRoute.size(); i++) {
                outFile << cur.walkingRoute[i];
                if (i < cur.walkingRoute.size() - 1) outFile << ",";
            }
            outFile << "(" << cur.walkingTime << ")\n";
        }
    
        outFile << "TotalTime" << i+1 << ":";
        if (cur.time == 0) outFile << "\n";
        else outFile << cur.time << '\n';
    }

}



void EcoRoute::processRoute(ostream &outFile) {
    bool success = calculateRoute();
    writeToFile(outFile);
    if (!success) calculateAproxSolution(outFile);    
}