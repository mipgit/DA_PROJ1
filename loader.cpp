#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "Location.h"
#include "Distance.h"
#include "loader.h"
#include "cityMap.h"
using namespace std;



map<string, Location> locations;
vector<Distance> distances;


Graph<Location> cityMap;



// ===== LOADING FUNCTIONS =====

// Load Locations.csv
void loadLocations(const string &filename)
{
    locations.clear();

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "\nError opening Locations file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {

        stringstream ss(line);
        string name, id, code, parking;

        getline(ss, name, ',');
        getline(ss, id, ',');
        getline(ss, code, ',');
        getline(ss, parking, ',');

        Location loc(name, stoi(id), code, stoi(parking));
        locations[code] = loc;
    }

    file.close();
    cout << "\nLoaded " << locations.size() << " locations successfully.\n";
}

// Load Distances.csv
void loadDistances(const string &filename)
{
    distances.clear();

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "\nError opening Distances file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string loc1, loc2, driv, walk;

        getline(ss, loc1, ',');
        getline(ss, loc2, ',');
        getline(ss, driv, ',');
        getline(ss, walk, ',');

        Location l1 = locations[loc1];
        Location l2 = locations[loc2];

        if (driv == "X") driv = "-1";
        if (walk == "X") walk = "-1"; 
        Distance dist(l1, l2, stoi(driv), stoi(walk));
        distances.push_back(dist);
    }

    file.close();
    cout << "\nLoaded " << distances.size() << " distances successfully.\n";
}


// MISSPLACED DISPLAYS

// Show Locations
void displayLocations()
{
    if (locations.empty())
    {
        cout << "\nNo locations loaded.\n";
        return;
    }

    cout << "\nAvailable Locations:\n";
    for (auto l : locations)
    {
        cout << l.second.getLocation() << " (" << l.second.getCode() << ")"
             << "\nID: " << l.second.getId()
             << "\nParking: " << (l.second.hasParking() ? "Yes" : "No") << "\n"
             << '\n';
    }
}

// Show Distances
void displayDistances()
{
    if (distances.empty())
    {
        cout << "\nNo distances loaded.\n";
        return;
    }

    cout << "\nAvailable Distances:\n";
    for (auto d : distances)
    {

        Location l1 = d.getSource();
        Location l2 = d.getDestination();
        int driv = d.getDriving();
        double walk = d.getWalking();


        cout << l1.getLocation() << " -> " << l2.getLocation()
             << "\nDriving: " << driv << " min"
             << "\nWalking: " << walk << " min\n\n";
    }
}




// ===== GRAPH FUNCTIONS =====


void initializeGraph() {

    cityMap = Graph<Location> (); //limpa 

    //add locations as vertices
    for (auto &l : locations) {
        cityMap.addVertex(l.second);
    }

    for (auto &d : distances) {
        Location l1 = d.getSource(); 
        Location l2 = d.getDestination();
        int driv = d.getDriving();
        double walk = d.getWalking();
        cityMap.addBidirectionalEdge(l1, l2, driv, walk);
    }

}



// graph testers
void displayVertices() {

    for (auto v : cityMap.getVertexSet()) {
        auto a = v->getInfo();
        cout << a.getLocation() << '\n';
    }

}


void testG() {
    cout << "Vertices:\n";
    initializeGraph();
    displayVertices();
}
















// TESTES
int main() {
    
    loadLocations("data_sets/Locations.csv");
    loadDistances("data_sets/Distances.csv");

    testG();

    return 0;
}