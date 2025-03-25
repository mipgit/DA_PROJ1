#ifndef DISTANCE_H
#define DISTANCE_H


#include "Location.h"
#include <string>
using namespace std;


class Distance
{
public:
    //if there is no distance, set it to 0
    Distance();
    //else
    Distance(Location l1, Location l2, int d, double w);

    
    Location getSource() const;
    Location getDestination() const; 
    int getDriving() const;
    double getWalking() const;

private:
    Location location1;
    Location location2;
    int driving;
    int walking;
};


#endif