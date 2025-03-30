/** @file Location.h
 *  @brief Contains the definition of the Location class.
 *
 *  This file defines the Location class, which represents a location with details 
 *  such as the name, unique ID, code, and parking availability. The class provides 
 *  methods to access and compare these details.
 */

#ifndef LOCATION_H
#define LOCATION_H


#include <string>
using namespace std;

/**
 * @class Location
 * @brief Represents a location with details such as name, ID, code, and parking availability.
 */
class Location {
    public:
        /**
         * @brief Default constructor that initializes a Location object with default values.
         *
         * Initializes the Location with empty values for the string fields and 0 for the ID, 
         * and sets parking availability to false.
         */
        Location();

        /**
         * @brief Constructor to initialize a Location object with the given details.
         *
         * @param l The name of the location.
         * @param id The unique identifier for the location.
         * @param code A code associated with the location.
         * @param p A boolean indicating if the location has parking available.
         */
        Location(string l, int id, string code, bool p);

        /**
         * @brief Gets the name of the location.
         * @return The name of the location as a string.
         */
        string getLocation() const;

        /**
         * @brief Gets the unique ID of the location.
         * @return The unique ID of the location as an integer.
         */
        int getId() const;

        /**
         * @brief Gets the code associated with the location.
         * @return The code of the location as a string.
         */
        string getCode() const;

        /**
         * @brief Checks if the location has parking available.
         * @return True if the location has parking, false otherwise.
         */
        bool hasParking() const;

        /**
         * @brief Compares two Location objects for equality.
         * 
         * @param other The Location object to compare to.
         * @return True if the two Location objects are equal, false otherwise.
         */
        bool operator==(const Location &other) const;

    private:
        string location; ///< The name of the location.
        int id;          ///< The unique identifier for the location.
        string code;     ///< The code associated with the location.
        bool parking;    ///< Indicates if the location has parking available.
};


#endif