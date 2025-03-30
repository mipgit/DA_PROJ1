// Code adapted from DA 24/25

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <utility>
#include "MutablePriorityQueue.h"

template <class T>
class Edge;

#define INF std::numeric_limits<int>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
public:
    Vertex(T in);       // in will be a Location
    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue

    T getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    bool isVisited() const;
    double getDist() const;
    Edge<T> *getPath() const;
    std::vector<Edge<T> *> getIncoming() const;

    void setInfo(T info);
    void setVisited(bool visited);

    void setDist(double dist);
    void setPath(Edge<T> *path);
    Edge<T> * addEdge(Vertex<T> *dest, double d, double w);
    bool removeEdge(T in);
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;
protected:
    T info;                // info node
    std::vector<Edge<T> *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    double dist = 0;
    Edge<T> *path = nullptr;

    std::vector<Edge<T> *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge<T> *edge);
};

/********************** Edge  ****************************/

template <class T>
class Edge
{
public:
    Edge(Vertex<T> *orig, Vertex<T> *dest, double d, double w);

    Vertex<T> *getDest() const;
    double getDriving() const;
    double getWalking() const;
    Vertex<T> *getOrig() const;
    Edge<T> *getReverse() const;

    void setDriving(double d);
    void setWalking(double w);
    void setReverse(Edge<T> *reverse);

protected:
    Vertex<T> *dest; // destination vertex
    double driving;  // driving distance
    double walking;  // walking distance

    // used for bidirectional edges
    Vertex<T> *orig;
    Edge<T> *reverse = nullptr;
};

/********************** Graph  ****************************/

template <class T>
class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex<T> *findVertex(const T &in) const;

    /*
    * Auxiliary function to find a vertex with a given id.
    */
    Vertex<T> *findLocationId(const int &id);

    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const T &in);
    bool removeVertex(const T &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const T &sourc, const T &dest, double d, double w);
    bool removeEdge(const T &source, const T &dest);
    bool addBidirectionalEdge(const T &sourc, const T &dest, double d, double w);

    int getNumVertex() const;


    /*
     *  Removes a set of vertices from a graph.
     */
    void avoidVertices(std::vector<int> vertices);

    /*
     *  Removes a set of edges from a graph.
     */
    void avoidEdges(std::vector<std::pair<int,int>> edges);


    std::vector<Vertex<T> *> getVertexSet() const;


protected:
    std::vector<Vertex<T> *> vertexSet;    // vertex set

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const T &in) const;

};

/*
 * Returns a copy of a given graph.
 */
template <class T>
Graph<T>* copyGraph(Graph<T> *g);

/************************* Vertex  **************************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
Edge<T> * Vertex<T>::addEdge(Vertex<T> *dest, double d, double w) {
    auto newEdge = new Edge<T>(this, dest, d, w);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdge(T in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        Vertex<T> *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
template <class T>
void Vertex<T>::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
std::vector<Edge<T>*> Vertex<T>::getAdj() const {
    return this->adj;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return this->visited;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Edge<T> *Vertex<T>::getPath() const {
    return this->path;
}

template <class T>
std::vector<Edge<T> *> Vertex<T>::getIncoming() const {
    return this->incoming;
}

template <class T>
void Vertex<T>::setInfo(T in) {
    this->info = in;
}

template <class T>
void Vertex<T>::setVisited(bool visited) {
    this->visited = visited;
}

template <class T>
void Vertex<T>::setDist(double dist) {
    this->dist = dist;
}

template <class T>
void Vertex<T>::setPath(Edge<T> *path) {
    this->path = path;
}

template <class T>
void Vertex<T>::deleteEdge(Edge<T> *edge) {
    Vertex<T> *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

template <class T>
Edge<T>::Edge(Vertex<T> *orig, Vertex<T> *dest, double d, double w) : orig(orig), dest(dest), driving(d), walking(w) {}

template <class T>
Vertex<T> *Edge<T>::getDest() const
{
    return this->dest;
}

template <class T>
double Edge<T>::getDriving() const
{
    return this->driving;
}

template <class T>
double Edge<T>::getWalking() const
{
    return this->walking;
}

template <class T>
Vertex<T> *Edge<T>::getOrig() const
{
    return this->orig;
}

template <class T>
Edge<T> *Edge<T>::getReverse() const
{
    return this->reverse;
}

template <class T>
void Edge<T>::setDriving(double driving)
{
    this->driving = driving;
}

template <class T>
void Edge<T>::setWalking(double walking)
{
    this->walking = walking;
}

template <class T>
void Edge<T>::setReverse(Edge<T> *reverse)
{
    this->reverse = reverse;
}

/********************** Graph  ****************************/

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}


// find Location given an id
template <class T>
Vertex<T> * Graph<T>::findLocationId(const int &id) {
    for (auto v : vertexSet) {
        auto t = v->getInfo();
        if (t.getId() == id) return v;
    }
    return nullptr;
}


/*
 * Finds the index of the vertex with a given content.
 */
template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getInfo() == in)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double d, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, d, w);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, double d, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, d, w);
    auto e2 = v2->addEdge(v1, d, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}


template <class T>
Graph<T>::~Graph() {}



template<class T>
void Graph<T>::avoidVertices(std::vector<int> vertices) {
    if (!vertices.empty()) {
        for (auto id : vertices) {
            Vertex<T>* loc = findLocationId(id);
            if(loc) removeVertex(loc->getInfo());     // if it isn't nullptr
        }
    }
}


template<class T>
void Graph<T>::avoidEdges(std::vector<std::pair<int,int>> edges) {
    if (!edges.empty()) {
        for (auto p : edges) {
            int sId = p.first;
            int dId = p.second;
    
            Vertex<T>* source = findLocationId(sId);
            Vertex<T>* dest = findLocationId(dId);
    
            if(source!=nullptr && dest!=nullptr) source->removeEdge(dest->getInfo());
        }
    }
}


template <class T>
Graph<T>* copyGraph(Graph<T>* g) {
    Graph<T>* gC = new Graph<T>();

    // we add the vertices
    for (auto v : g->getVertexSet()) {
        gC->addVertex(v->getInfo());
    }

    // and build the edges
    for (auto v : g->getVertexSet()) {
        for (auto e : v->getAdj()) {
            gC->addBidirectionalEdge(v->getInfo(), e->getDest()->getInfo(), e->getDriving(), e->getWalking());
        }
    }

    return gC;
}


#endif /* DA_TP_CLASSES_GRAPH */