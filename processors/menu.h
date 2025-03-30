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

/** @file menu.h
 *  @brief Contains functions for user interaction and route selection.
 *
 *  This file defines functions that handle user input for selecting routes and modes
 *  and initiates the processing of selected routes in either interactive or batch mode.
 */

/**
 * @brief Handles the interactive mode for route selection and processing.
 *
 * @param cityMap Pointer to the graph representing the city.
 * @param choice User's selected route type.
 */
void interactMode(Graph<Location>* cityMap, char choice);

/**
 * @brief Handles the batch mode for processing routes from a file.
 *
 * @param cityMap Pointer to the graph representing the city.
 * @param choice User's selected route type.
 */
void batchMode(Graph<Location>* cityMap, char choice);

/**
 * @brief Allows the user to choose between interactive and batch modes.
 *
 * @param cityMap Pointer to the graph representing the city.
 * @param choice User's selected route type.
 */
void chooseMode(Graph<Location>* cityMap, char choice);

/**
 * @brief Presents the user with different route planning options.
 *
 * @param cityMap Pointer to the graph representing the city.
 */
void chooseRoute(Graph<Location>* cityMap);


#endif