#ifndef LOADER_H
#define LOADER_H


#include <string>
#include <map>
#include <vector>
#include "Location.h"
#include "Distance.h"
#include "data_structures/Graph.h"
using namespace std;


// maps
extern map<string, Location> locations;
extern vector<Distance> distances;

// graph
//extern Graph<Location> cityMap;


// Load Locations.csv
void loadLocations(const string &filename);

// Load Distances.csv
void loadDistances(const string &filename);


// Initialization of main Graph
Graph<Location>* initializeGraph();


//testers
void displayLocations();
void displayDistances();
void displayVertices();
void displayEdges();


#endif 