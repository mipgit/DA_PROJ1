#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "processors/loader.h"
#include "processors/menu.h"

using namespace std;


// ===== MAIN FUNCTION =====


/**
 * @file main.cpp
 * @brief Main function of the program.
 *
 * This function serves as the entry point of the program. It loads the necessary data sets,
 * initializes the graph representing the city map, and then presents the user with a menu 
 * to choose the type of route to calculate. The program's execution is then concluded 
 * by deleting the graph object to free allocated memory.
 *
 * - Loads the locations from the "Locations.csv" file.
 * 
 * - Loads the distances from the "Distances.csv" file.
 * 
 * - Initializes the graph that represents the city map.
 * 
 * - Starts a menu, calling the `chooseRoute` function to allow the user to select a route, which will call `chooseMode` to select a menu mode.
 * 
 * - Frees the dynamically allocated memory used by the graph object.
 *
 * @return 0 to indicate successful execution of the program.
 */
int main() {
    
    // Load data sets
    loadLocations("../data_sets/LittleLocations.csv");
    loadDistances("../data_sets/LittleDistances.csv");

    Graph<Location>* cityMap = initializeGraph();

    chooseRoute(cityMap);

    delete cityMap;
    return 0;
}