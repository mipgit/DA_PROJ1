#ifndef RESROUTE_H
#define RESROUTE_H


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


class RestrictedRoute : public Route {

    public:

        RestrictedRoute(Graph<Location>* mp) : Route(mp,"",-1,-1), avoidNodes(), avoidSegs(), node(-1), time(0), route(), route2() {}

        RestrictedRoute(Graph<Location>* mp, string m, int src, int dt, vector<int> avoidN, vector<pair<int, int>> avoidS) 
            :  Route(mp,m,src,dt), avoidNodes(avoidN), avoidSegs(avoidS), node(-1), time(0), route(), route2() {}
        
        bool readFromFile(const string &filename) override;
        void writeToFile(ostream &outFile) override;
        void calculateRoute();

        void processRoute(ostream &outFile) override;


    private:
        vector<int> avoidNodes;
        vector<pair<int,int>> avoidSegs;
        int node;
        int time;
        vector<int> route;
        vector<int> route2;

};



#endif