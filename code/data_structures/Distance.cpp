#include "Distance.h"
using namespace std;

Distance::Distance() : location1(), location2(), driving(0), walking(0) {}
Distance::Distance(Location l1, Location l2, int d, double w) : location1(l1), location2(l2), driving(d), walking(w) {}

Location Distance::getSource() const {return location1;}
Location Distance::getDestination() const {return location2;}
int Distance::getDriving() const { return driving; }
double Distance::getWalking() const { return walking; }

