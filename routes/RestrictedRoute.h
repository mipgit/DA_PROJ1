#ifndef RESROUTE_H
#define RESROUTE_H


#include "Route.h"


using namespace std;

/**
 * @class RestrictedRoute
 * @brief Class for handling route calculation with restrictions, extending the Route class.
 *
 * This class calculates a route between a source and destination on a given map with specific routing restrictions. 
 * It enables users to avoid undesirable areas, excluding specific nodes from the graph.
 * It enables users to avoid undesirable road segments, excluding specific segments from the graph.
 * It enables users to simultaneously exclude the combination of nodes and segments of the graph.
 * It enables users to include a single specific node (or stop) that the route must include while ensuring that the calculated route remains the fastest possible
 */
class RestrictedRoute : public Route {

    public:
        /**
         * @brief Default constructor for RestrictedRoute.
         * 
         * Initializes a RestrictedRoute object with the provided map, mode, source, and destination. 
         * Sets up restrictions for nodes and edges.
         * 
         * @param map A pointer to the Graph representing the map with locations.
         */
        RestrictedRoute(Graph<Location>* map) : Route(map,"",-1,-1), avoidNodes(), avoidSegs(), node(-1), time(0), route() {}

        /**
         * @brief Constructor for RestrictedRoute with specific mode, source, destination, and restrictions.
         * 
         * Initializes a RestrictedRoute object with the provided parameters, setting up restrictions
         * on nodes and segments, as well as the node where the route must end.
         * 
         * @param map A pointer to the Graph representing the map with locations.
         * @param m A string representing the mode of transportation ("driving", "driving-walking").
         * @param src The ID of the source location.
         * @param dt The ID of the destination location.
         * @param avoidN A vector of node IDs to avoid during the route calculation.
         * @param avoidS A vector of pairs representing edge segments to avoid (start, end).
         * @param inc The ID of a node to include on the path.
         */    
        RestrictedRoute(Graph<Location>* map, string m, int src, int dt, vector<int> avoidN, vector<pair<int, int>> avoidS, int inc) 
            :  Route(map,m,src,dt), avoidNodes(avoidN), avoidSegs(avoidS), node(inc), time(0), route() {}
        
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
         * @brief Calculates the route while avoiding certain nodes and edges.
         * 
         * This method calculates the route while considering the restricted areas, such as avoiding specific nodes 
         * and segments. It updates the route and time variables accordingly.
         */
        void calculateRoute();


        /**
         * @brief Processes the route, calling `calculateRoute` and `writeToFile`.
         * @param outFile The output stream where the processed route results will be written.
         */
        void processRoute(ostream &outFile) override;


    private:
        vector<int> avoidNodes;  ///< Vector of node IDs to avoid during the route calculation.
        vector<pair<int, int>> avoidSegs;  ///< Vector of edge segments to avoid, represented as pairs of node IDs (start, end).
        int node;  ///< The ID of the node that needs to be included.
        int time;  ///< The total time for the calculated route.
        vector<int> route;  ///< Vector holding the IDs of the vertices in the calculated route.

};



#endif