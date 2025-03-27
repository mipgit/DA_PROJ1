#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "Location.h"
#include "IndependentRoute.h"
#include "RestrictedRoute.h"
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

        while (true) {
            cout << "Mode (driving/walking): ";
            std::cin >> mode;
            if (mode == "driving" || mode == "walking") break;
            cout << "Invalid mode! Please enter 'driving' or 'walking'.\n";
        }

        cout << "Source id: ";
        cin >> source;

        cout << "Destination id: ";
        cin >> dest;

        
        //falta validar inputs antes de avançar

        Route* route = nullptr;

        vector<int> avoidNodes;
        vector<pair<int, int>> avoidSegs;
        string s, node, a, seg;
        stringstream nodes(s), segs(a);
        
        switch(choice) {
            case 1:
                route = new IndependentRoute(cityMap, mode, source, dest);
                break;

            case 2:

                //NAO ESTÁ A FUNCIONAR!!!!
                cout << "AvoidNodes:";
                getline(cin, s);
                //stringstream nodes(s);
                while(getline(nodes, node, ',')) avoidNodes.push_back(stoi(node));

                cout << "\nAvoidSegments:";
                getline(cin, a);
                //stringstream segs(a);
                while(getline(segs, seg, ')')) {
                    if(!seg.empty()) {
                        stringstream pairNodes(seg); 
                        int src, dst;
                        pairNodes.ignore();
                        pairNodes >> src;
                        pairNodes.ignore();
                        pairNodes >> dst;
                        if (src>0 && dst>0) avoidSegs.push_back(make_pair(src, dst));
                        
                    }
                }

                route = new RestrictedRoute(cityMap, mode, source, dest, avoidNodes, avoidSegs);
                
                break;

            case 3:

                break;

            default:
                cout << "Invalid choice. Exiting...\n";
                exit(0);
        }


        cout << "\nResults are here!\n";
        if (route) {
            route->processRoute(cout);
            delete route; // free mem
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

    
    Route* route = nullptr;

    switch(choice) {
        case 1:
            route = new IndependentRoute(cityMap);
            break;

        case 2:
            route = new RestrictedRoute(cityMap);

        case 3:
            route = new RestrictedRoute(cityMap);

        default:
            cout << "\nInvalid\n";
            break;

    }

    if (route) {
        if (route->readFromFile(inputFileName)) {
            ofstream file(outputFileName);
            route->processRoute(file);
            cout << "Route calculation completed. Results saved to " << outputFileName << '\n';
        } else {
            cerr << "Route calculation failed.\n\n";
        }

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

