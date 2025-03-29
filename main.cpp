#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "loader.h"
#include "menu.h"

using namespace std;


// ===== MAIN FUNCTION =====

int main() {
    
    // Load data sets
    int inFileSize = loadLocations("../data_sets/LittleLocations.csv");
    loadDistances("../data_sets/LittleDistances.csv");

    Graph<Location>* cityMap = initializeGraph();

    chooseRoute(cityMap, inFileSize);

    delete cityMap;

    return 0;
}