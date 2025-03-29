#include "Location.h"
using namespace std;


//empty
Location::Location() : location(""), id(0), code(""), parking(false) {} 
//else
Location::Location(string l, int id, string code, bool p) : location(l), id(id), code(code), parking(p) {}

string Location::getLocation() const { return location; }
int Location::getId() const { return id; }
string Location::getCode() const { return code; }
bool Location::hasParking() const { return parking; }

bool Location::operator==(const Location &other) const {
    return (id == other.id) && (code == other.code);
}