#include "loader.h"
using namespace std;


map<string, Location> locations;
vector<Distance> distances;


// ===== LOADING FUNCTIONS =====

// load Locations.csv
int loadLocations(const string &filename){
    locations.clear();

    int fSize = 0;

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "\nError opening Locations file: " << filename << endl;
        return fSize;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {

        fSize ++;

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
    cout << "\nLoaded " << locations.size() << " locations successfully.";

    return fSize;
}

// load Distances.csv
void loadDistances(const string &filename){
    
    distances.clear();

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "\nError opening Distances file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string loc1, loc2, driv, walk;
        int d_num, w_num;

        getline(ss, loc1, ',');
        getline(ss, loc2, ',');
        getline(ss, driv, ',');
        getline(ss, walk, ',');

        Location l1 = locations[loc1];
        Location l2 = locations[loc2];

        // if driv or walk = "X"
        try {d_num = stoi(driv);}
        catch (const invalid_argument &e) {d_num = INF;}

        try {w_num = stoi(walk);}
        catch (const invalid_argument &e) {w_num = INF;}

        Distance dist(l1, l2, d_num, w_num);
        distances.push_back(dist);
    }

    file.close();
    cout << "\nLoaded " << distances.size() << " distances successfully.\n\n";
}

// ===== GRAPH FUNCTIONS =====

Graph<Location> *initializeGraph() {

    Graph<Location> *cityMap = new Graph<Location>();

    // add locations as vertices
    for (auto &l : locations) {
        cityMap->addVertex(l.second);
    }

    // process distances as edges
    for (auto &d : distances) {
        Location l1 = d.getSource();
        Location l2 = d.getDestination();
        int driv = d.getDriving();
        double walk = d.getWalking();
        cityMap->addBidirectionalEdge(l1, l2, driv, walk);
    }

    return cityMap;
}

/*

// MISSPLACED DISPLAYS -> TESTERS

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


// Show Vertices
void displayVertices() {
    for (auto vertex : cityMap->getVertexSet()) {
        auto loc = vertex->getInfo();
        cout << loc.getLocation() << '\n';
    }
}

// Show Edges
void displayEdges() {
    for (auto vertex : cityMap->getVertexSet()) {
        auto loc = vertex->getInfo();
        cout << "Vertex " << loc.getLocation() << " -> \n";
        for (auto edge : vertex->getAdj()) {
            auto loc2 = edge->getDest()->getInfo();
            cout << "(" << loc2.getLocation() << ", Driving: " << edge->getDriving()
                      << ", Walking: " << edge->getWalking() << ") \n";
        }
        cout << '\n';
    }
}



*/