#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "loader.h"
#include "menu.cpp"


using namespace std;



// ===== MAIN FUNCTION =====

int main() {
    
    // Load data sets
    loadLocations("data_sets/LittleLocations.csv");
    loadDistances("data_sets/LittleDistances.csv");

    Graph<Location>* cityMap = initializeGraph();

    routePlan(cityMap);

    delete cityMap;

    return 0;
}