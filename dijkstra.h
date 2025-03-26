#ifndef DIJKSTRA_H
#define DIJKSTRA_H


#include "data_structures/Graph.h"
#include "data_structures/MutablePriorityQueue.h"

using namespace std;

template <class T>
bool relax(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDist() + edge->getDriving() < edge->getDest()->getDist()) {
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getDriving());
        edge->getDest()->setPath(edge);
        return true;
    }
    return false;
}


template <class T>
void dijkstra(Graph<T> * g, const int &origin, const int &dest) {

    if (g->getVertexSet().empty()) return;

    //inicializar as variaveis auxiliares
    for (Vertex<T> *v : g->getVertexSet()) { 
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    //encontrar ids
    Vertex<T> *s = g->findLocationId(origin);
    Vertex<T> *d = g->findLocationId(dest);
    s->setDist(0);

    if (!s || !d) return;

    //inicializamos a fila de prioridade
    MutablePriorityQueue<Vertex<T>> pq;
    pq.insert(s);

    //processamos os nós da queue
    while (!pq.empty()) {
        Vertex<T>* v = pq.extractMin();
        v->setVisited(true);

        if (v == d) return;

        for (auto e : v->getAdj()) {
            Vertex<T> *w = e->getDest();
            if (!w->isVisited()) {
                double oldDist = e->getDest()->getDist();
                if (relax(e)) {
                    if (oldDist == INF) pq.insert(e->getDest());
                    else pq.decreaseKey(e->getDest());
                }
            }
        }
    }

}

template <class T>
static std::vector<int> getPath(Graph<T> * g, const int &origin, const int &dest) {
    std::vector<int> res;
    Vertex<T> *s = g->findLocationId(dest);
    if (s == nullptr) return res;
    res.push_back(s->getInfo().getId());

    while (s->getPath() != nullptr) {
        s = s->getPath()->getOrig();
        res.push_back(s->getInfo().getId());
    }

    reverse(res.begin(), res.end());
    return res;
}

#endif