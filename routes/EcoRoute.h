#ifndef ECOROUTE_H
#define ECOROUTE_H

#include "Route.h"
using namespace std;

/**
 * @brief Structure to store an approximate solution when an exact route is not found. Used in EcoRoute.
 */
struct AproxSolution {
    vector<int> drivingRoute; ///< The driving route as a sequence of node IDs.
    int drivingTime; ///< Time taken for the driving part of the journey.
    int parkingNode; ///< The parking node where the driver stops.
    vector<int> walkingRoute; ///< The walking route as a sequence of node IDs.
    int walkingTime; ///< Time taken for the walking part of the journey.
    int time; ///< Total time for the route.
};


/**
 * @class EcoRoute
 * @brief Class for handling environmentally-friendly route calculation, extending the Route class.
 * 
 * This class implements the best (shortest overall) route for driving and walking, ensuring that it meets user-defined constraints.
 * The best route includes at least one driving segment and one walking segment, minimizing both driving and walking time.
 * Should there be two or more feasible routes with the same overall minimum travel time, it selects the one with the longest walking section.
 * 
 * If no suitable route is found, it displays a list of suggestions representing the best feasible alternative routes that approximate user requirements.
 */
class EcoRoute : public Route {

    public:

        /**
         * @brief Default constructor for EcoRoute.
         * @param map Pointer to the graph representing the city map.
         */
        EcoRoute(Graph<Location>* map) : Route(map,"",-1,-1), maxWalk(INF), parkingNode(-1), time(0), drivingTime(0), walkingTime(0) {}

        /**
         * @brief Parameterized constructor for EcoRoute.
         * @param map Pointer to the graph representing the city map.
         * @param m Route mode.
         * @param src Source node ID.
         * @param dt Destination node ID.
         * @param mw Maximum walking time allowed.
         * @param avoidN List of nodes to avoid.
         * @param avoidS List of edges to avoid (represented as pairs of node IDs).
         */
        EcoRoute(Graph<Location>* map, string m, const int src, const int dt, const int mw, const vector<int> &avoidN, const vector<pair<int, int>> &avoidS)
            :  Route(map,m,src,dt), maxWalk(mw), avoidNodes(avoidN), avoidSegs(avoidS), parkingNode(-1), time(0), drivingTime(0), walkingTime(0) {}

        /**
         * @brief Reads route data from a file.
         * @param filename Name of the file to read from.
         * @return True if reading was successful, false otherwise.
         */
        bool readFromFile(const string &filename) override;

        /**
         * @brief Writes route data to an output stream.
         * @param outFile Output stream to write the route data.
         */
        void writeToFile(ostream &outFile) override;

        /**
         * @brief Calculates the eco-friendly route with a combination of driving and walking.
         * @return True if a valid route is found, false otherwise.
         */
        bool calculateRoute();

        /**
         * @brief Calculates and writes a maximum of 2 approximate solutions in case an exact route isn't possible.
         * @param outFile Output stream to write the approximate solutions.
         */
        void calculateAproxSolution(ostream &outFile);

        /**
         * @brief Processes the route, calling `calculateRoute`, `writeToFile` and `calculateAproxSolution`, if `calculateRoute` isn't successful.
         * @param outFile The output stream where the processed route results will be written.
         */
        void processRoute(ostream &outFile) override;


    private:
        vector<int> avoidNodes; ///< List of nodes to avoid in the route.
        vector<pair<int, int>> avoidSegs; ///< List of edges to avoid (represented as pairs of node IDs).
        int maxWalk; ///< Maximum walking time allowed.
        int parkingNode; ///< The selected parking node.
        int time; ///< Total time for the route.
        vector<int> drivingRoute; ///< The driving route as a sequence of node IDs.
        int drivingTime; ///< Time taken for the driving portion of the journey.
        vector<int> walkingRoute; ///< The walking route as a sequence of node IDs.
        int walkingTime; ///< Time taken for the walking portion of the journey.

        string message; ///< Stores error messages if the route cannot be computed.

        vector<AproxSolution> aproxSolutions; ///< Stores alternative route solutions when the main route isn't possible.

        /**
         * @brief Finds available parking locations.
         * @param source The starting node ID.
         * @param dest The destination node ID.
         * @return A vector containing parking node IDs.
         */
        vector<int> findParking(int source, int dest);

};



#endif