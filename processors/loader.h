#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "../data_structures/Location.h"
#include "../data_structures/Distance.h"
#include "../data_structures/Graph.h"

using namespace std;

/** @file loader.h
 *  @brief Contains functions to load location and distance data into memory.
 *
 *  This file implements functions to read location and distance data from CSV files
 *  and initialize the main graph structure.
 */

//maps
extern map<string, Location> locations;    ///< Stores locations indexed by their codes.
extern vector<Distance> distances;         ///< Stores distances between locations.


/**
 * @brief Loads location data from a CSV file.
 *
 * @param filename The name of the CSV file containing location data.
 */
void loadLocations(const string &filename);

/**
 * @brief Loads distance data from a CSV file.
 *
 * @param filename The name of the CSV file containing distance data.
 */
void loadDistances(const string &filename);


/**
 * @brief Initializes the main graph using loaded location and distance data.
 *
 * @return A pointer to the initialized graph.
 */
Graph<Location>* initializeGraph();


//testers

/**
 * @brief Displays all loaded locations.
 */
void displayLocations();

/**
 * @brief Displays all loaded distances.
 */
void displayDistances();

/**
 * @brief Displays all vertices in the graph.
 */
void displayVertices();

/**
 * @brief Displays all edges in the graph.
 */
void displayEdges();


#endif 