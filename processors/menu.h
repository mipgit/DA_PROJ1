#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "utils.h"
#include "../routes/IndependentRoute.h"
#include "../routes/RestrictedRoute.h"
#include "../routes/EcoRoute.h"
#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
using namespace std;

void interactMode(Graph<Location>* cityMap, char choice);
void batchMode(Graph<Location>* cityMap, char choice);
void chooseMode(Graph<Location>* cityMap, char choice);
void chooseRoute(Graph<Location>* cityMap);

#endif