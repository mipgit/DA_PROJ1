#ifndef ECOROUTE_H
#define ECOROUTE_H


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


class EcoRoute : public Route {

    public:

        EcoRoute(Graph<Location>* mp) : Route(mp,"",-1,-1), maxWalk(0), avoidNodes(), avoidSegs(), time(0), route() {}

        EcoRoute(Graph<Location>* mp, string m, int src, int dt) 
            :  Route(mp,m,src,dt), maxWalk(0), avoidNodes(), avoidSegs(), time(0), route() {}
        
        bool readFromFile(const string &filename) override;
        void writeToFile(ostream &outFile) override;
        void calculateRoute();

        void processRoute(ostream &outFile) override;


    private:
        int maxWalk;
        vector<int> avoidNodes;
        vector<pair<int,int>> avoidSegs;
        int time;
        vector<int> route;

};



#endif