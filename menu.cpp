#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "Location.h"
#include "IndRoute.h"
using namespace std;


// ======== MENU ========


// ===== MODE =====

//por agora vamos assumir que escolhe sempre a opçao 1
void interactMode(Graph<Location>* cityMap, int choice) {
    string mode;
    int source = -1, dest = -1;
    //depois vao ser precisas mais cenas... (see T2.2)

    bool keepRunning = true;

    while (keepRunning) {

        cout << "======== ENTER INFO ========\n";

        cout << "Mode (driving/walking): ";
        std::cin >> mode;

        cout << "Source id: ";
        cin >> source;

        cout << "Destination id: ";
        cin >> dest;

        
        //falta validar inputs antes de avançar

        IndRoute indr(cityMap, mode, source, dest);
        
        switch(choice) {
            case 1:
                cout << "\nResults are here!\n";
                indr.processRoute(cout);
                break;

            case 2:
                //do
                break;

            default:
                cout << "Invalid choice. Exiting...\n";
                exit(0);
        }


        cout << "\nDo you want to process another route? (y/n): ";
        char userChoice;
        cin >> userChoice;

        if (userChoice == 'n' || userChoice == 'N') {
            keepRunning = false;  // exit the loop
            cout << "Going to mode panel...\n\n";

        } else if (userChoice != 'y' && userChoice != 'Y') {
            cout << "Invalid choice. Exiting...\n";
            exit(0);
        }


    } 
}


//por agora vamos assumir que escolhe sempre a opçao 1
void batchMode(Graph<Location>* cityMap, int choice) {
    string inputFileName, outputFileName;

    cout << "Enter input file name: ";
    cin >> inputFileName;
    cout << "Enter output file name: ";
    cin >> outputFileName;  

    
    //assumimos choice=1
    IndRoute indr(cityMap);

    if (indr.readFromFile(inputFileName)) {
        ofstream file(outputFileName);
        indr.processRoute(file);
        cout << "Route calculation completed. Results saved to " << outputFileName << '\n';
    } else {
        cerr << "Route calculation failed.\n\n";
    }
    
}


void chooseMode(Graph<Location>* cityMap, int choice) {

    int mode;
    
    do {
        cout << "======== CHOOSE MODE ========\n";
        cout << "1. Interactive mode\n";
        cout << "2. Batch mode\n";
        cout << "0. Exit\n";
        cout << "Select an option: ";
        cin >> mode;
        cin.ignore();

        switch(mode) {
            case 1:
                cout << "\nGoing to interactive mode...\n\n";
                interactMode(cityMap, choice);
                break;

            case 2:
                cout << "\nGoing to batch mode...\n";
                batchMode(cityMap, choice);
                break;
            
            case 0:
                cout << "\nExiting...\n";
                exit(0);
            
            default:
                cout << "\nInvalid option. Please try again.\n";
        }
    } while (mode != 0);

}



// ===== PLAN =====
void routePlan(Graph<Location>* cityMap) {

    int choice;

    do {
        cout << "======== CHOOSE YOUR ROUTE PLAN ========\n\n";

        cout << "1. Independent Route Planning -> driving\n";
        cout << "2. Restricted Route Planning -> driving\n";
        
        cout << "3. Best route for driving and walking\n";

        cout << "0. Exit\n";

        cout << "Select an option: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
            case 2:
            case 3:
                cout << "\nGreat! Going to next step...\n\n";
                chooseMode(cityMap, choice);
                break;

            case 0:
                cout << "\nExiting...\n";
                break;
            
            default:
                cout << "\nInvalid option. Please try again.\n";
        }

    } while (choice != 0);

}

