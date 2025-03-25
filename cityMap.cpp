#include "loader.h"
#include "data_structures/Graph.h"
#include <iostream>


/*
map<string, Location> locations;
vector<Distance> distances;
*/

Graph<Location> cityMap;

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
