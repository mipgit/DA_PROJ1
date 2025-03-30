/** @file IndependentRoute.h
 *  @brief Contains the definition of the IndependentRoute class.
 *
 *  This file defines the IndependentRoute class, which calculates two independent routes 
 *  between a source and destination. The two routes are independent and share no intermediate 
 *  nodes or segments except for the source and destination.
 */

#ifndef INDEPENDENTROUTE_H
#define INDEPENDENTROUTE_H

#include "Route.h"

using namespace std;

/**
 * @class IndependentRoute
 * @brief Class for handling independent route calculation, extending the Route class.
 *
 * This class calculates the best route and an alternative route between a source and destination on a given map.
 * The two routes share no intermediate nodes or segments, except for the source and destination,
 * and that the alternative route is equal to or greater in travel time than the primary route.
 * This provides a robust “Plan-B” option for navigation.
 */
class IndependentRoute : public Route {

    public:

        /**
         * @brief Default constructor for IndependentRoute.
         * 
         * Initializes an IndependentRoute object with the provided map, mode, source, and destination. 
         * Sets up best and alternative route variables.
         * 
         * @param map A pointer to the Graph representing the map with locations.
         */
        IndependentRoute(Graph<Location>* map) : Route(map,"",-1,-1), bestTime(0), altTime(0) {}


        /**
         * @brief Constructor for IndependentRoute with specific mode, source, and destination.
         * 
         * Initializes an IndependentRoute object with the provided parameters. 
         * Sets up the best and alternative route variables based on the provided mode and locations.
         * 
         * @param map A pointer to the Graph representing the map with locations.
         * @param m A string representing the mode of transportation ("driving", "driving-walking").
         * @param src The ID of the source location.
         * @param dt The ID of the destination location.
         */
        IndependentRoute(Graph<Location>* map, string m, const int src, const int dt)
            :  Route(map, m, src, dt), bestTime(0), altTime(0) {}
        
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
         * @brief Calculates the best route between the source and destination.

         * It updates the bestRoute and bestTime member variables.
         */
        void calculateBestRoute();

        /**
         * @brief Calculates the alternative route between the source and destination.
         * 
         * This method calculates the best alternative route, that shares no intermediate nodes or segments with the best one.
         * It updates the altRoute and altTime member variables.
         */
        void calculateAltRoute();

        /**
         * @brief Processes the route, calling `calculateBestRoute`, `calculateAltRoute` and `writeToFile`.
         * @param outFile The output stream where the processed route results will be written.
         */
        void processRoute(ostream &outFile) override;

    private:
        vector<int> bestRoute;  ///< Vector holding the best route's vertex IDs.
        vector<int> altRoute;   ///< Vector holding the alternative route's vertex IDs.
        int bestTime;           ///< Total time for the best route.
        int altTime;            ///< Total time for the alternative route.

};



#endif
