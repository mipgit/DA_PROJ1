/** @file Distance.h
 *  @brief Contains the definition of the Distance class.
 *
 *  This file defines the Distance class, which represents the distance between 
 *  two locations. The class stores both driving and walking distances between 
 *  two specific locations and provides methods to retrieve these distances and the locations.
 */

#ifndef DISTANCE_H
#define DISTANCE_H


#include "Location.h"
#include <string>
using namespace std;


/**
 * @class Distance
 * @brief Represents the distance between two locations, including both driving and walking distances.
 */
class Distance {
    public:
        /**
         * @brief Default constructor that sets distance to 0.
         *
         * This constructor initializes the distance to 0 when no specific locations or distances 
         * are provided.
         */
        Distance();
    
        /**
         * @brief Constructor to initialize a Distance object with two locations, driving distance, 
         *        and walking distance.
         *
         * @param l1 The first location.
         * @param l2 The second location.
         * @param d The driving distance between the locations.
         * @param w The walking distance between the locations.
         */
        Distance(Location l1, Location l2, int d, double w);
    
        /**
         * @brief Gets the source location.
         * @return The source location.
         */
        Location getSource() const;
    
        /**
         * @brief Gets the destination location.
         * @return The destination location.
         */
        Location getDestination() const; 
    
        /**
         * @brief Gets the driving distance between the locations.
         * @return The driving distance.
         */
        int getDriving() const;
    
        /**
         * @brief Gets the walking distance between the locations.
         * @return The walking distance.
         */
        double getWalking() const;
    
    private:
        Location location1; ///< The first location.
        Location location2; ///< The second location.
        int driving;        ///< The driving distance.
        double walking;     ///< The walking distance.
};


#endif