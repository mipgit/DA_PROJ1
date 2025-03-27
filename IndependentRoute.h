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
#include "Route.h"

using namespace std;


class IndependentRoute : public Route {

    public:

        IndependentRoute(Graph<Location>* mp) : Route(mp,"",-1,-1), bestTime(0), altTime(0), bestRoute(), altRoute() {}

        IndependentRoute(Graph<Location>* mp, string m, int src, int dt) 
            :  Route(mp, m, src, dt), bestTime(0), altTime(0), bestRoute(), altRoute() {}
        
        bool readFromFile(const string &filename) override;
        void writeToFile(ostream &outFile) override;
        void calculateBestRoute();
        void calculateAltRoute();

        void processRoute(ostream &outFile) override;

    private:
        vector<int> bestRoute;
        vector<int> altRoute;
        int bestTime;
        int altTime;

};



#endif
