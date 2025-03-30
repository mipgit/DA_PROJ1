#include "menu.h"
using namespace std;


// ======== MENU ========


// ================================= ROUTE =================================

void chooseRoute(Graph<Location>* cityMap) {

    char choice;

    do {
        cout << "======== CHOOSE YOUR ROUTE PLAN ========\n";
        cout << "1. Independent Route Planning -> driving\n";
        cout << "2. Restricted Route Planning -> driving\n";
        cout << "3. Best route for driving and walking\n";
        cout << "E. Exit\n";
        cout << "Select an option: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case '1':
            case '2':
            case '3':
                cout << "\nGreat! Going to next step...\n\n";
                chooseMode(cityMap, choice);
                break;

            case 'e':
            case 'E':
                cout << "\nExiting...\n";
                break;

            default:
                cout << "\nInvalid option. Please try again.\n\n";
        }

    } while (choice != 'e' && choice != 'E');

}





// ================================= MODE =================================

void chooseMode(Graph<Location>* cityMap, char choice) {

    char mode;

    do {
        cout << "======== CHOOSE MODE ========\n";
        cout << "1. Interactive mode\n";
        cout << "2. Batch mode\n";
        cout << "R. Go back to route selection\n";
        cout << "E. Exit\n";
        cout << "Select an option: ";
        cin >> mode;
        cin.ignore();

        switch(mode) {
            case '1':
                cout << "\nGoing to interactive mode...\n\n";
                interactMode(cityMap, choice);
                break;

            case '2':
                cout << "\nGoing to batch mode...\n";
                batchMode(cityMap, choice);
                break;

            case 'r':
            case 'R':
                 cout << "\nGoing to route selection panel...\n\n";
                 return;

            case 'e':
            case 'E':
                cout << "\nExiting...\n";
                exit(0);

            default:
                cout << "\nInvalid option. Please try again.\n\n";
        }
    } while (mode != 'e' && mode != 'E' && mode != 'r' && mode != 'R');

}





void interactMode(Graph<Location>* cityMap, char choice) {
    string mode;
    int source = -1, dest = -1;

    bool keepRunning = true;

    while (keepRunning) {

        cout << "======== ENTER INFO ========\n";

        
        while (true) {
            cout << "Mode: ";
            cin >> mode;

            if (choice == '1' || choice == '2') {
                if (mode == "driving") break;
                else {cout << "Invalid mode! Please enter 'driving'.\n";}

            } else if (choice == '3') {
                if (mode == "driving-walking") break;
                else {cout << "Invalid mode! Please enter 'driving-walking'.\n";}

            } else {
                cout << "Invalid mode! Try again.\n";
            }
            
        }

        while (true) {
            string tempSource;

            cout << "Source: ";
            cin >> tempSource;
            try {
                int s = stoi(tempSource);
                if (cityMap->findLocationId(s) != nullptr) {
                    source = s;
                    break;
                } else {
                    cout << "Invalid source id! Please enter a node id present in the graph.\n";
                }
            } catch (const invalid_argument& e) {
                cout << "Invalid source ID! Please enter a valid integer.\n";
            } 
        }

        while (true) {
            string tempDest;
            cout << "Destination: ";
            cin >> tempDest;
            try {
                int d = stoi(tempDest);
                if (cityMap->findLocationId(d) != nullptr) {
                    dest = d;
                    break;
                } else {
                    cout << "Invalid dest id! Please enter a node id present in the graph.\n";
                }
            } catch (const invalid_argument& e) {
                cout << "Invalid dest ID! Please enter a valid integer.\n";
            } 
        }

        

        // we initialize a Route object
        Route* route = nullptr;


   		// depending on the choice made on Route Panel, we proceed
        switch(choice) {
            case '1':
                route = new IndependentRoute(cityMap, mode, source, dest);
                break;

            case '2': {
                vector<int> avoidNodes;
                vector<pair<int, int>> avoidSegs;
                string n, node, s, seg, includeNode;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                bool flag = false;
                
                while(!flag) {

                    cout << "AvoidNodes: ";
                    getline(cin, n);
                    stringstream nodes(n);

                    if (n.empty()) {  
                        flag = true;
                        break;
                    }
                
                    while (getline(nodes, node, ',')) {
                        if (!node.empty()){
                            try {
                                int id = stoi(node);
                                if (id == source || id == dest) {
                                    cout << "Can't avoid source/dest nodes!\n";
                                    flag = false;
                                    break;
                                } else {
                                    avoidNodes.push_back(id);
                                    flag = true;
                                }
                            } catch (const invalid_argument& e) {
                                cout << "Invalid node ID to avoid.\n";
                                flag = false;
                            } 
                        }
                    }
                }

                flag = false;
                
                while(!flag) {

                    cout << "AvoidSegments: ";
                    getline(cin, s);
                    stringstream segs(s);

                    if (s.empty()) {
                        flag = true; 
                        break;
                    }
                    
                    while (getline(segs, seg, ')')) {
                        
                        if (!seg.empty()) {
                        
                            // "(src,dest" -> "src,dest"
                            seg.erase(remove(seg.begin(), seg.end(), '('), seg.end());
                    
                            stringstream pairNodes(seg);
                            int src, dst;
                            char comma;
                        
                            // we extract src and dest
                            if (pairNodes >> src >> comma >> dst && comma == ',') {

                                if (cityMap->findLocationId(src) != nullptr && cityMap->findLocationId(dst) != nullptr) {
                                    avoidSegs.push_back(make_pair(src, dst));
                                    flag = true;
                                    break;
                                } else {
                                    cout << "Invalid ID(s)! Please enter ID(s) present in the graph.\n";
                                    flag = false;
                                }

                            } else {
                                cout << "Invalid segment format.\n";
                                flag = false;
                            }
                        
                        }
                    
                    
                        //the comma separating segments
                        char separator;
                        segs >> separator; 
                    }

                }

                int inNode;
                flag = false;

                while (!flag) {
                    cout << "IncludeNode: ";
                    getline(cin, includeNode);
        
                    if (!includeNode.empty()) {
                    
                        try {
                            int n = stoi(includeNode);
                            if (cityMap->findLocationId(n) != nullptr) {
                                inNode = n;
                                flag = true;
                                break;
                            } else {
                                cout << "Invalid node ID! Please enter a node ID present in the graph.\n";
                                flag = false;
                            }
                        } catch (const invalid_argument& e) {
                            cout << "Invalid node ID! Please enter a valid integer.\n";
                            flag = false;
                        }

                    } else {
                        inNode = -1;    // default value when user inputs nothing
                        flag = true;
                    }
                }
                

                // finally...
                route = new RestrictedRoute(cityMap, mode, source, dest, avoidNodes, avoidSegs, inNode);
                break;
            }

            case '3': {
                vector<int> avoidNodes;
                vector<pair<int, int>> avoidSegs;
                string n, node, s, seg, maxWalk;
                int maxWalkTime;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');


                while (true) {
                    cout << "MaxWalkTime: ";
                    getline(cin, maxWalk);

                    if (!maxWalk.empty()) {
                        try {
                            maxWalkTime = stoi(maxWalk);
                            if (maxWalkTime <= 0) {  
                                cout << "MaxWalkTime must be a positive integer!\n";
                                continue;
                            }
                            break;  
                
                        } catch (const invalid_argument&) {
                            cout << "Invalid input! Please enter a valid integer.\n";
                        }
                    }
                    
                    else cout << "MaxWalkTime is mandatory! Please enter a time.\n"; 
                }


                bool flag = false;
                
                while(!flag) {

                    cout << "AvoidNodes: ";
                    getline(cin, n);
                    stringstream nodes(n);

                    if (n.empty()) {  
                        flag = true;
                        break;
                    }
                
                    while (getline(nodes, node, ',')) {
                        if (!node.empty()){
                            try {
                                int id = stoi(node);
                                if (id == source || id == dest) {
                                    cout << "Can't avoid source/dest nodes!\n";
                                    flag = false;
                                    break;
                                } else {
                                    avoidNodes.push_back(id);
                                    flag = true;
                                }
                            } catch (const invalid_argument& e) {
                                cout << "Invalid node ID to avoid.\n";
                                flag = false;
                            } 
                        }
                    }
                }

                flag = false;
                
                while(!flag) {

                    cout << "AvoidSegments: ";
                    getline(cin, s);
                    stringstream segs(s);

                    if (s.empty()) {
                        flag = true; 
                        break;
                    }
                    
                    while (getline(segs, seg, ')')) {
                        
                        if (!seg.empty()) {
                        
                            // "(src,dest" -> "src,dest"
                            seg.erase(remove(seg.begin(), seg.end(), '('), seg.end());
                    
                            stringstream pairNodes(seg);
                            int src, dst;
                            char comma;
                        
                            // we extract src and dest
                            if (pairNodes >> src >> comma >> dst && comma == ',') {

                                if (cityMap->findLocationId(src) != nullptr && cityMap->findLocationId(dst) != nullptr) {
                                    avoidSegs.push_back(make_pair(src, dst));
                                    flag = true;
                                    break;
                                } else {
                                    cout << "Invalid ID(s)! Please enter ID(s) present in the graph.\n";
                                    flag = false;
                                }

                            } else {
                                cout << "Invalid segment format.\n";
                                flag = false;
                            }
                        
                        }
                    
                        //the comma separating segments
                        char separator;
                        segs >> separator; 
                    }

                }

                                

                // finally
                route = new EcoRoute(cityMap, mode, source, dest, maxWalkTime, avoidNodes, avoidSegs);
                break;
            }

            default:
                cout << "Invalid choice. Exiting...\n";
                exit(0);
                break;
        }


        cout << "\nResults are here!\n\n";
        if (route) {
            route->processRoute(cout);
            delete route; // free mem
        }

        

        cout << "\nDo you want to process another route? (y/n): ";
        char userChoice;
        cin >> userChoice;

        while (userChoice != 'y' && userChoice != 'Y' && userChoice != 'n' && userChoice != 'N') {
            cout << "Invalid choice. Please enter 'y' for yes or 'n' for no: ";
            cin >> userChoice;
        }


        if (userChoice == 'n' || userChoice == 'N') {

            cout << "\nDo you want to go back to the mode selection panel or exit? (m/e): ";
            char nextChoice;
            cin >> nextChoice;

            while (nextChoice != 'm' && nextChoice != 'M' && nextChoice != 'e' && nextChoice != 'E') {
                cout << "Invalid choice. Please enter 'm' for mode panel or 'e' for exit: ";
                cin >> nextChoice;
            }

            if (nextChoice == 'm' || nextChoice == 'M') {
                keepRunning = false;  // exit the loop
                cout << "Going to mode panel...\n\n";
            } else {
                cout << "Exiting...\n";
                exit(0);
            }
        }

        else cout << endl;

    } 
}


void batchMode(Graph<Location>* cityMap, char choice) {       // falta fazer o controlo de erro dos nodes no batchMode
    string inputFileName, outputFileName;
    string inputFilePath, outputFilePath;

    cout << "Enter input file path/name: ";
    cin >> inputFileName;
    inputFilePath = getFullPath(inputFileName);

    cout << "Enter output file path/name: ";
    cin >> outputFileName;
    outputFilePath = getFullPath(outputFileName);

    
    Route* route = nullptr;

    switch(choice) {
        case '1':
            route = new IndependentRoute(cityMap);
            break;

        case '2':
            route = new RestrictedRoute(cityMap);
            break;

        case '3':
            route = new EcoRoute(cityMap);
            break;

        default:
            cout << "\nInvalid route choice. Exiting...\n";
            exit(0);
            break;

    }

    if (route) {
        ofstream file(outputFilePath);
        if (route->readFromFile(inputFilePath)) {
            route->processRoute(file);
            cout << "Route calculation completed. Results saved to " << outputFileName << '\n';
        } else {
            cerr << "Route calculation failed.\n\n";
        }
        exit(0);
    }

    
    
}