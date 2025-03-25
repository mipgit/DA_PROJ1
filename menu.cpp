#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "loader.h"
using namespace std;


// ===== MENU =====
void mainMenu()
{
    int choice;
    string filename;


    do
    {
        cout << "Mode:\n\n";
        string mode;
        cin >> mode;

        cout << "Source:\n";
        
        //CONTINUAR
        cout << "0. Exit\n";
        cout << "Select an option: ";
        cin >> choice;
        cin.ignore(); // ignore the newline character left in the buffer

        switch (choice)
        {
        case 1:
            cout << "\nLoading Locations data from embedded Locations.csv...\n";
            loadLocations("data_sets/Locations.csv");
            break;
        case 2:
            if(locations.empty())
            {
                cout << "\nPlease load Locations data first.\n";
                break;
            }
            cout << "\nLoading Distances data from embedded Distances.csv...\n";
            loadDistances("data_sets/Distances.csv");
            break;
        
        case 0:
            cout << "\nExiting...\n";
            break;
        default:
            cout << "\nInvalid option. Please try again.\n";
        }

    } while (choice != 0);
}


void batchMode() {
    cout << "To implement\n";    
}


// ===== MODE =====
void chooseMode() {
    int mode;
    cout << "Choose mode:\n";
    cout << "1. Bla mode\n";
    cout << "2. Batch mode\n";
    cout << "0. Exit\n";
    cout << "Select an option: ";
    cin >> mode;
    cin.ignore();

    if (mode == 1) mainMenu();
    if (mode == 2) batchMode();
    return;
}


// ===== MAIN FUNCTION =====
int main() {
    
    // Load data sets
    loadLocations("data_sets/Locations.csv");
    loadDistances("data_sets/Distances.csv");

    chooseMode();
    return 0;
}
