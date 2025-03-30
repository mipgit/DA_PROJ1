#ifndef DIJKSTRA_H
#define DIJKSTRA_H


#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"

using namespace std;

/** @file dijkstra.h
 *  @brief Contains the implementation of Dijkstra's algorithm.
 *
 *  This file implements the function `dijkstra` that calculates the shortest path 
 *  between two vertices in a graph.
 */



/**
 * @brief Relaxes an edge if a shorter path is found.
 *
 * @tparam T Type of the graph vertices.
 * @param edge The edge being relaxed.
 * @param mode The mode of transportation (true for driving, false for walking).
 * @return True if the edge was relaxed, false otherwise.
 */
template <class T>
bool relax(Edge<T> *edge, bool mode) { // d[u] + w(u,v) < d[v]
    if (mode) {
        if (edge->getOrig()->getDist() + edge->getDriving() < edge->getDest()->getDist()) {
            edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getDriving());
            edge->getDest()->setPath(edge);
            return true;
        }
        return false;
    }

    if (edge->getOrig()->getDist() + edge->getWalking() < edge->getDest()->getDist()) {
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWalking());
        edge->getDest()->setPath(edge);
        return true;
    }
    return false;
   
}


/**
 * @brief Initializes all vertices for running Dijkstra's algorithm.
 *
 * @tparam T Type of the graph vertices.
 * @param g Pointer to the graph.
 * @return True if initialization was successful, false if the graph is empty.
 */
template <class T>
bool initDijkstra(Graph<T> * g) {

    if (g->getVertexSet().empty()) return false;
    
    //we init variables
    for (Vertex<T> *v : g->getVertexSet()) { 
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    return true;
}


/**
 * @brief Runs Dijkstra's shortest path algorithm from a source to a destination.
 *
 * @tparam T Type of the graph vertices.
 * @param g Pointer to the graph.
 * @param origin The ID of the starting vertex.
 * @param dest The ID of the destination vertex.
 * @param mode The mode of transportation (true for driving, false for walking).
 */
template <class T>
void dijkstra(Graph<T> * g, const int &origin, const int &dest, bool mode) {

    //we find ids
    Vertex<T> *s = g->findLocationId(origin);
    Vertex<T> *d = g->findLocationId(dest);
    if (!s || !d) return;

    s->setDist(0);

    //we init priority queue
    MutablePriorityQueue<Vertex<T>> pq;
    pq.insert(s);

    //process queue vertices
    while (!pq.empty()) {
        Vertex<T>* v = pq.extractMin();
        v->setVisited(true);

        if (v == d) return;

        for (auto e : v->getAdj()) {
            Vertex<T> *w = e->getDest();
            if (!w->isVisited()) {
                double oldDist = e->getDest()->getDist();
                if (relax(e, mode)) {
                    if (oldDist == INF) pq.insert(e->getDest());
                    else pq.decreaseKey(e->getDest());
                }
            }
        }
    }

}


/**
 * @brief Retrieves the shortest path from the origin to the destination.
 *
 * @tparam T Type of the graph vertices.
 * @param g Pointer to the graph.
 * @param origin The ID of the starting vertex.
 * @param dest The ID of the destination vertex.
 * @return A vector containing the path from origin to destination.
 */
template <class T>
vector<int> getPath(Graph<T> * g, const int &origin, const int &dest) {
    vector<int> res;
    Vertex<T> *s = g->findLocationId(dest);
    if (s == nullptr || s->getDist() == INF) return res;
    res.push_back(s->getInfo().getId());

    while (s->getPath() != nullptr) {
        s = s->getPath()->getOrig();
        res.push_back(s->getInfo().getId());
    }

    reverse(res.begin(), res.end());
    return res;
}

#endif