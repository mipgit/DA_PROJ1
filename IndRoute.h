#ifndef INDROUTE_H
#define INDROUTE_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>

#include "data_structures/Graph.h"
#include "Location.h"
#include "dijkstra.h"


using namespace std;


class IndRoute {

    public:

        IndRoute(Graph<Location>* mp) : cityMap(mp), source(-1), dest(-1), bestTime(0), altTime(0), bestRoute(), altRoute() {}

        IndRoute(Graph<Location>* mp, string m, int src, int dt) :  cityMap(mp), mode(m), source(src), dest(dt), bestTime(0), altTime(0), bestRoute(), altRoute() {}
        bool readFromFile(const string &filename);
        void writeToFile(ostream &outFile);
        void calculateBestRoute();
        void calculateAltRoute();

        void processRoute(ostream &outFile);

    private:
        Graph<Location>* cityMap;
        string mode;
        int source;
        int dest;
        vector<int> bestRoute;
        vector<int> altRoute;
        int bestTime;
        int altTime;

};



#endif
