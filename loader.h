#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "data_structures/Location.h"
#include "data_structures/Distance.h"
#include "data_structures/Graph.h"
using namespace std;


// maps
extern map<string, Location> locations;
extern vector<Distance> distances;


// load Locations.csv
int loadLocations(const string &filename);

// load Distances.csv
void loadDistances(const string &filename);


// initialization of main Graph
Graph<Location>* initializeGraph();


//testers
void displayLocations();
void displayDistances();
void displayVertices();
void displayEdges();


#endif 