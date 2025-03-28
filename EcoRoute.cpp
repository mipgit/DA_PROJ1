#include <iostream>
#include "EcoRoute.h"

using namespace std;



vector<int> EcoRoute::findParking() {
    vector<int> parkingNodes;
    for (auto vertex : cityMap->getVertexSet()) {
        if (vertex->getInfo().hasParking()) {
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

        // tiramos espaços
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
        
        else {
            cout << "Invalid input format in " << filename << "\n\n";
            return false;
        }
    }

    inFile.close();
    return true;
}


void EcoRoute::writeToFile(ostream &outFile) {

    outFile << "Source:" << source << "\n";
    outFile << "Destination:" << dest << "\n";
    
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
    if (time == 0) outFile << "none\n";
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
    else outFile << time << '\n';


    if (message!="") {
        outFile << "Message:" << message;
    }
}









void EcoRoute::calculateRoute() {
    
    Graph<Location>* copy = copyGraph(cityMap);

    copy->avoidVertices(avoidNodes);
    copy->avoidEdges(avoidSegs);

    int minTotalTime = numeric_limits<int>::max();
    bool validRoute = false;
    string failureReason = "No possible routes.\n";


    // finds all parking nodes
    vector<int> parkingNodes = findParking();

    if (parkingNodes.empty()) failureReason = "No available parking nodes.\n";



    for (int parking : parkingNodes) {
        dijkstra(copy, source, parking, 1);
        vector<int> drivingPath = getPath(copy, source, parking);
        if (drivingPath.empty()) continue; 

        int dt = copy->findLocationId(parking)->getDist();

        dijkstra(copy, parking, dest, 0);
        vector<int> walkingPath = getPath(copy, parking, dest);
        if (walkingPath.empty()) continue; 

        int wt = copy->findLocationId(dest)->getDist();

        if (wt > maxWalk) {
            failureReason = "All walking routes exceed max walking time.\n";
            continue;
        } 

        int totalTime = dt + wt;

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

    if (!validRoute) message = failureReason;
    delete copy;
}

// 1 2 3 . 7 8 - 15 + 45 = 60
// 1 2 . 4 8 - 10 + 25 + 18 = 53
// 1 2 3 



void EcoRoute::processRoute(ostream &outFile) {
    calculateRoute();
    writeToFile(outFile);    
}