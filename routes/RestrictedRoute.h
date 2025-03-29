#ifndef RESROUTE_H
#define RESROUTE_H


#include "Route.h"


using namespace std;


class RestrictedRoute : public Route {

    public:

        RestrictedRoute(Graph<Location>* mp) : Route(mp,"",-1,-1), avoidNodes(), avoidSegs(), node(-1), time(0), route() {}

        RestrictedRoute(Graph<Location>* mp, string m, int src, int dt, vector<int> avoidN, vector<pair<int, int>> avoidS, int in) 
            :  Route(mp,m,src,dt), avoidNodes(avoidN), avoidSegs(avoidS), node(in), time(0), route() {}
        
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

};



#endif