#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

class Location
{
public:
    //empty
    Location() : location(""), id(0), code(""), parking(false) {} 
    //else
    Location(string l, int id, string code, bool p) : location(l), id(id), code(code), parking(p) {}

    string getLocation() const { return location; }
    int getId() const { return id; }
    string getCode() const { return code; }
    bool hasParking() const { return parking; }

private:
    string location;
    int id;
    string code;
    bool parking;
};

class Distance
{
public:
    //if there is no distance, set it to 0
    Distance() : location1("", 0, "", false), location2("", 0, "", false), driving(0), walking(0.0) {}
    //else
    Distance(Location l1, Location l2, int d, double w) : location1(l1), location2(l2), driving(d), walking(w) {}

    int getDriving() const { return driving; }
    double getWalking() const { return walking; }

private:
    Location location1;
    Location location2;
    int driving;
    int walking;
};

// ===== STRUCTURES =====
map<string, Location> locations;
map<pair<string, string>, Distance> distances;

// ===== FUNCTIONS =====

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
        distances[{loc1, loc2}] = dist;
    }

    file.close();
    cout << "\nLoaded " << distances.size() << " distances successfully.\n";
}

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
        Location l1 = locations[d.first.first];
        Location l2 = locations[d.first.second];
        int driv = d.second.getDriving();
        double walk = d.second.getWalking();


        cout << l1.getLocation() << " -> " << l2.getLocation()
             << "\nDriving: " << driv << " min"
             << "\nWalking: " << walk << " min\n\n";
    }
}

// ===== MENU =====
void mainMenu()
{
    int choice;
    string filename;

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Load Locations Data\n";
        cout << "2. Load Distances Data\n";
        cout << "3. Show Locations\n";
        cout << "4. Show Distances\n";
        cout << "0. Exit\n";
        cout << "Select an option: ";
        cin >> choice;
        cin.ignore(); // ignore the newline character left in the buffer

        switch (choice)
        {
        case 1:
            cout << "\nEnter path for Locations.csv: ";
            getline(cin, filename);
            loadLocations(filename);
            break;
        case 2:
            if(locations.empty())
            {
                cout << "\nPlease load Locations data first.\n";
                break;
            }
            cout << "\nEnter path for Distances.csv: ";
            getline(cin, filename);
            loadDistances(filename);
            break;
        case 3:
            displayLocations();
            break;
        case 4:
            displayDistances();
            break;
        case 0:
            cout << "\naff tchau.....!\n";
            break;
        default:
            cout << "\nInvalid option. Please try again.\n";
        }

    } while (choice != 0);
}

// ===== MAIN FUNCTION =====
int main()
{
    mainMenu();
    return 0;
}
