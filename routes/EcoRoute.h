#ifndef ECOROUTE_H
#define ECOROUTE_H

#include "Route.h"
using namespace std;


struct AproxSolution {
    vector<int> drivingRoute;
    int drivingTime;
    int parkingNode;
    vector<int> walkingRoute;
    int walkingTime;
    int time;
};


class EcoRoute : public Route {

    public:

        EcoRoute(Graph<Location>* mp) : Route(mp,"",-1,-1), maxWalk(INF), avoidNodes(), avoidSegs(), parkingNode(-1), time(0), drivingTime(0), walkingTime(0), message("") {}

        EcoRoute(Graph<Location>* mp, string m, int src, int dt, int mw, vector<int> avoidN, vector<pair<int, int>> avoidS) 
            :  Route(mp,m,src,dt), maxWalk(mw), avoidNodes(avoidN), avoidSegs(avoidS), parkingNode(-1), time(0), drivingTime(0), walkingTime(0), message("") {}
        
        bool readFromFile(const string &filename) override;
        void writeToFile(ostream &outFile) override;
        bool calculateRoute();
        void calculateAproxSolution(ostream &outFile);

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

        //in case of error a message is printed w/info
        string message;

        //if the error is concerning maxWalk, we have to provide 2 alternatives
        vector<AproxSolution> aproxSolutions;

        vector<int> findParking(int source, int dest);

};





#endif