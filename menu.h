#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "data_structures/Location.h"
#include "routes/IndependentRoute.h"
#include "routes/RestrictedRoute.h"
#include "routes/EcoRoute.h"
#include "data_structures/Graph.h"
using namespace std;

void interactMode(Graph<Location>*, int, int);
void batchMode(Graph<Location>*, int, int);
void chooseMode(Graph<Location>*, int, int);
void chooseRoute(Graph<Location>*, int);

#endif // MENU_H