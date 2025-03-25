#ifndef CITYMAP_H
#define CITYMAP_H


#include "data_structures/Graph.h"
#include "Location.h"


extern Graph<Location> cityMap;

void initializeGraph();
void displayVertices();
void testG();

#endif