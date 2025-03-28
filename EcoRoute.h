#ifndef ECOROUTE_H
#define ECOROUTE_H


#include "Route.h"


using namespace std;


class EcoRoute : public Route {

    public:

        EcoRoute(Graph<Location>* mp) : Route(mp,"",-1,-1), avoidNodes(), avoidSegs(), maxWalk(INF), parkingNode(-1), time(0), drivingTime(0), walkingTime(0), message("") {}

        EcoRoute(Graph<Location>* mp, string m, int src, int dt, vector<int> avoidN, vector<pair<int, int>> avoidS, int mw) 
            :  Route(mp,m,src,dt), avoidNodes(avoidN), avoidSegs(avoidS), maxWalk(mw), parkingNode(-1), time(0), drivingTime(0), walkingTime(0), message("") {}
        
        bool readFromFile(const string &filename) override;
        void writeToFile(ostream &outFile) override;
        void calculateRoute();

        void processRoute(ostream &outFile) override;


    private:
        vector<int> avoidNodes;
        vector<pair<int,int>> avoidSegs;
        int maxWalk;
        int parkingNode;
        int time;
        vector<int> drivingRoute;
        int drivingTime;
        vector<int> walkingRoute;
        int walkingTime;

        string message;

        vector<int> findParking();

};



#endif