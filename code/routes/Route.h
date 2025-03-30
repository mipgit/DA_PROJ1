/** @file Route.h
 *  @brief Defines the abstract Route class for calculating routes between a source and destination.
 *
 *  This file defines the abstract class `Route`, which serves as a base class for different types 
 *  of route calculations (e.g., independent, restricted, eco-friendly). It provides a common interface 
 *  for handling the calculation and processing of routes based on a source and destination on a city map. 
 *  Derived classes are expected to implement specific route processing and data handling (e.g., reading and 
 *  writing routes from/to files).
 *  
 *  The Route class relies on a graph representation of locations (`Graph<Location>`) and supports different 
 *  modes of transportation (e.g., driving, driving-walking).
 */

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


/**
 * @class Route
 * @brief Abstract class representing a route between a source and destination.
 *
 * This class provides an interface for classes that define specific types of routes 
 * (independent, restriced or eco-friendly), allowing the calculation and processing of routes 
 * based on a source and destination location on a map.
 */
class Route {
    public:
        /**
         * @brief Constructor for Route.
         * 
         * Initializes a Route object with the given parameters: a map, mode, source, and destination.
         * 
         * @param map A pointer to the Graph representing the map with locations.
         * @param m A string representing the mode of transportation (driving, driving-walking).
         * @param src The ID of the source location.
         * @param dt The ID of the destination location.
         */
        Route(Graph<Location>* map, string m, const int src, const int dt)
            : cityMap(map), mode(m), source(src), dest(dt) {}
        
        /**
         * @brief Virtual destructor for the Route class.
         * Ensures proper cleanup of derived classes when an object is destroyed.
         */    
        virtual ~Route() = default;

        /**
         * @brief Reads the route data from a file.
         * 
         * This is a pure virtual function, which must be implemented in derived classes to 
         * handle reading the route information from a file.
         * 
         * @param filename The name of the file to read.
         * @return True if reading was successful, false otherwise.
         */
        virtual bool readFromFile(const string &filename) = 0;


        /**
         * @brief Writes the route data to an output stream (e.g., a file or console).
         * 
         * This is a pure virtual function, which must be implemented in derived classes to 
         * handle writing the route information to an output stream.
         * 
         * @param outFile The output stream to write the data to (could be a file or std::cout).
         */        
        virtual void writeToFile(ostream &outFile) = 0;


        /**
         * @brief Processes the route, which may involve calculations, optimizations, or other actions.
         * 
         * This is a pure virtual function, which must be implemented in derived classes to 
         * handle processing of the route based on the specific route type.
         * 
         * @param outFile The output stream to which results will be written.
         */    
        virtual void processRoute(ostream &outFile) = 0;
    
    protected:
        Graph<Location>* cityMap; ///< Pointer to the graph representing the city map with locations.
        string mode;              ///< Mode of transportation (e.g., "driving" or "driving-walking").
        int source;               ///< ID of the source location.
        int dest;                 ///< ID of the destination location.
};

#endif // ROUTE_H
