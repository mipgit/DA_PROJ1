#ifndef LOCATION_H
#define LOCATION_H


#include <string>
using namespace std;


class Location
{
public:
    //empty
    Location();
    //else
    Location(string l, int id, string code, bool p);

    string getLocation() const;
    int getId() const;
    string getCode() const;
    bool hasParking() const;

    bool operator==(const Location &other) const;

private:
    string location;
    int id;
    string code;
    bool parking;
};


#endif