#include "IndRoute.h"

using namespace std;




bool IndRoute::readFromFile(const string &filename) {
    
    ifstream inFile(filename);

    if (!inFile ) {
        cout << "\nError opening files.\n";
        return false;
    }

    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string key, value;

        getline(ss, key, ':');  // por exemplo, "Mode:"
        getline(ss, value);     // por exemplo, "driving"

        // tiramos espaços
        while (!value.empty() && value.front() == ' ') {
            value.erase(0, 1);
        }

        if (key == "Mode" && value == "driving") mode = value;
        else if (key == "Source" && stoi(value) > 0) source = stoi(value);
        else if (key == "Destination" && stoi(value) > 0) dest = stoi(value);
        else {
            cout << "Invalid input format in " << filename << "\n\n";
            return false;
        }
    }

    inFile.close();
    return true;
}


void IndRoute::writeToFile(ostream &outFile) {

    outFile << "Source: " << source << "\n";
    outFile << "Destination: " << dest << "\n";
    
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


void IndRoute::calculateBestRoute() {


    if (!cityMap) {
        cout << "Error: cityMap is not initialized.\n";
        return;
    }
    
    dijkstra(cityMap, source, dest); // Ensure cityMap is a pointer to a valid Graph object
    
    // Get the best route path
    bestRoute = getPath(cityMap, source, dest);

    // Calculate the bestTime
    Vertex<Location> *destVertex = cityMap->findLocationId(dest);
    bestTime = destVertex->getDist();
  
}



void IndRoute::calculateAltRoute() {
    
    Graph<Location>* copy = copyGraph(cityMap);

    for (int i = 1; i < bestRoute.size()-2; i++) {
        int id = bestRoute[i];
        Vertex<Location>* loc = copy->findLocationId(id);

        if(loc) copy->removeVertex(loc->getInfo());     // if it isn't nullptr
    }

    dijkstra(copy, source, dest);

    altRoute = getPath(copy, source, dest);

    Vertex<Location> *destVertex = copy->findLocationId(dest);
    altTime = destVertex->getDist();

    delete copy;
}


void IndRoute::processRoute(ostream &outFile) {
    calculateBestRoute();
    //calculateAltRoute();
    writeToFile(outFile);    
}