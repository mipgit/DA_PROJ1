#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "dijkstra.h"

using namespace std;

class Route {
    public:
        Route(Graph<Location>* mp, string m, int src, int dt) 
            : cityMap(mp), mode(m), source(src), dest(dt) {}
        
        virtual ~Route() {}
        virtual bool readFromFile(const string &filename) = 0;
        virtual void writeToFile(ostream &outFile) = 0;
        virtual void processRoute(ostream &outFile) = 0;
    
    protected:
        Graph<Location>* cityMap;
        string mode;
        int source;
        int dest;
};

#endif // ROUTE_H
