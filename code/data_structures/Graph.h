/** @file Graph.h
 *  @brief Contains the declaration of the Graph, Vertex, and Edge classes.
 * 
 *  The code is adapted from DA 24/25
 *
 *  This file implements a graph structure, including vertices and edges, 
 *  and provides methods to manipulate and query the graph. It supports 
 *  operations such as adding/removing vertices and edges, finding vertices, 
 *  and handling bidirectional edges. It also provides functionality for 
 *  graph traversal and manipulation, including avoiding certain vertices or edges.
 */

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


/**
 * @brief Defines an infinite value for edge weights.
 */
#define INF std::numeric_limits<int>::max()



/************************* Vertex  **************************/

/**
 * @class Vertex
 * @brief Class representing a vertex in the graph.
 *
 * @tparam T The type of the data stored in the vertex (e.g., Location).
 */
template <class T>
class Vertex {
public:

    /**
     * @brief Constructor to initialize a vertex with the given data.
     * @param in The data (e.g., Location) for this vertex.
     */
    Vertex(T in);       

    /**
     * @brief Overload of the less-than operator.
     * @param vertex The vertex to compare to.
     * @return 
     */
    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue


    /**
     * @brief Gets the data (info) of the vertex.
     * @return The data stored in this vertex.
     */
    T getInfo() const;

    /**
     * @brief Gets the list of outgoing edges from this vertex.
     * @return A vector of pointers to outgoing edges.
     */
    std::vector<Edge<T> *> getAdj() const;

    /**
     * @brief Checks if the vertex has been visited.
     * @return True if the vertex has been visited.
     */
    bool isVisited() const;

    /**
     * @brief Gets the distance value associated with the vertex.
     * @return The distance value.
     */
    double getDist() const;

    /**
     * @brief Gets the edge that leads to this vertex.
     * @return A pointer to the edge that leads to this vertex.
     */
    Edge<T> *getPath() const;

    /**
     * @brief Gets the list of incoming edges to this vertex.
     * @return A vector of pointers to incoming edges.
     */
    std::vector<Edge<T> *> getIncoming() const;

    /**
     * @brief Sets the data (info) of the vertex.
     * @param info The data to set.
     */
    void setInfo(T info);

    /**
     * @brief Sets whether the vertex has been visited.
     * @param visited True if the vertex has been visited.
     */
    void setVisited(bool visited);


    /**
     * @brief Sets the distance value associated with the vertex.
     * @param dist The distance value to set.
     */
    void setDist(double dist);

    /**
     * @brief Sets the path edge that leads to this vertex.
     * @param path A pointer to the edge leading to this vertex.
     */
    void setPath(Edge<T> *path);

    /**
     * @brief Adds an outgoing edge to another vertex.
     * @param dest The destination vertex for the edge.
     * @param d The driving distance of the edge.
     * @param w The walking distance of the edge.
     * @return A pointer to the created edge.
     */
    Edge<T> * addEdge(Vertex<T> *dest, double d, double w);

    /**
     * @brief Removes an outgoing edge to a specific destination vertex.
     * @param in The data (info) of the destination vertex.
     * @return True if the edge was removed.
     */
    bool removeEdge(T in);

    /**
     * @brief Removes all outgoing edges from this vertex.
     */
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;
protected:
    T info;                ///< Info node
    std::vector<Edge<T> *> adj;  ///< Outgoing edges

    // auxiliary fields
    bool visited = false;   ///< Indicates if the vertex has been visited
    double dist = 0;        ///< Distance value for algorithms (e.g., Dijkstra)
    Edge<T> *path = nullptr; ///< Path edge to this vertex

    std::vector<Edge<T> *> incoming; ///< Incoming edges

    int queueIndex = 0; 		///< Required by MutablePriorityQueue and UFDS

    /**
     * @brief Deletes a given edge from the vertex.
     * @param edge The edge to delete.
     */
    void deleteEdge(Edge<T> *edge);
};




/********************** Edge  ****************************/


/**
 * @class Edge
 * @brief Class representing an edge between two vertices in the graph.
 *
 * @tparam T The type of the data stored in the vertex (e.g., Location).
 */
template <class T>
class Edge
{
public:

    /**
     * @brief Constructor to initialize an edge with a given source, destination, distances, and weights.
     * @param orig The origin vertex.
     * @param dest The destination vertex.
     * @param d The driving distance.
     * @param w The walking distance.
     */
    Edge(Vertex<T> *orig, Vertex<T> *dest, double d, double w);

    /**
     * @brief Gets the destination vertex of the edge.
     * @return A pointer to the destination vertex.
     */
    Vertex<T> *getDest() const;

    /**
     * @brief Gets the driving distance of the edge.
     * @return The driving distance.
     */
    double getDriving() const;

    /**
     * @brief Gets the walking distance of the edge.
     * @return The walking distance.
     */
    double getWalking() const;

    /**
     * @brief Gets the origin vertex of the edge.
     * @return A pointer to the origin vertex.
     */
    Vertex<T> *getOrig() const;

    /**
     * @brief Gets the reverse edge (if it exists).
     * @return A pointer to the reverse edge.
     */
    Edge<T> *getReverse() const;

    /**
     * @brief Sets the driving distance of the edge.
     * @param d The driving distance to set.
     */
    void setDriving(double d);

    /**
     * @brief Sets the walking distance of the edge.
     * @param w The walking distance to set.
     */
    void setWalking(double w);

    /**
     * @brief Sets the reverse edge for this edge.
     * @param reverse A pointer to the reverse edge.
     */
    void setReverse(Edge<T> *reverse);

protected:
    Vertex<T> *dest; ///< destination vertex
    double driving;  ///< driving distance
    double walking;  ///< walking distance

    // used for bidirectional edges
    Vertex<T> *orig;     ///< The origin vertex
    Edge<T> *reverse = nullptr; ///< The reverse edge for bidirectional graphs

};




/********************** Graph  ****************************/

/**
 * @class Graph
 * @brief Class representing a graph consisting of vertices and edges.
 *
 * @tparam T The type of the data stored in the vertex (e.g., Location).
 */
template <class T>
class Graph {
public:
    /**
     * @brief Destructor that cleans up dynamically allocated vertices and edges.
     */
    ~Graph();

    /**
     * @brief Auxiliary function to find a vertex with a given the content.
     * @param in The data of the vertex to find.
     * @return A pointer to the vertex, or nullptr if not found.
     */
    Vertex<T> *findVertex(const T &in) const;


    /**
     * @brief Auxiliary function to find a vertex with a given id.
     * @param id The ID of the location to find.
     * @return A pointer to the vertex, or nullptr if not found.
     */
    Vertex<T> *findLocationId(const int &id);

    /**
     * @brief Adds a vertex with a given content or info (in) to a graph (this).
     * @param in The data for the vertex.
     * @return True if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const T &in);

    /**
     * @brief Removes a vertex with a given content or info (in) to a graph (this).
     * @param in The data for the vertex.
     * @return True if successful, and false if a vertex with that content already exists.
     */
    bool removeVertex(const T &in);

    /**
     * @brief Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * @param sourc The data of the source vertex.
     * @param dest The data of the destination vertex.
     * @param d The driving distance for the edge.
     * @param w The walking distance for the edge.
     * @return True if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const T &sourc, const T &dest, double d, double w);

    /**
     * @brief Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * @param sourc The data of the source vertex.
     * @param dest The data of the destination vertex.
     * @return True if successful, and false if the source or destination vertex does not exist.
     */
    bool removeEdge(const T &source, const T &dest);

    /**
     * @brief Adds a bidirectional edge between two vertices.
     * @param sourc The data of the source vertex.
     * @param dest The data of the destination vertex.
     * @param d The driving distance for the edge.
     * @param w The walking distance for the edge.
     * @return True if the bidirectional edge was added successfully, false if the vertices do not exist.
     */
    bool addBidirectionalEdge(const T &sourc, const T &dest, double d, double w);


    /**
     * @brief Gets the number of vertices in the graph.
     * @return The number of vertices.
     */
    int getNumVertex() const;


    /**
     * @brief Removes a set of vertices from the graph.
     * @param vertices A list of vertex IDs to remove.
     */
    void avoidVertices(std::vector<int> vertices);

    /**
     * @brief Removes a set of edges from the graph.
     * @param edges A list of pairs of vertex IDs representing the edges to remove.
     */
    void avoidEdges(std::vector<std::pair<int,int>> edges);

    /**
     * @brief Gets the set of vertices in the graph.
     * @return A vector of pointers to all vertices in the graph.
     */
    std::vector<Vertex<T> *> getVertexSet() const;


protected:
    std::vector<Vertex<T> *> vertexSet;    ///< vertex set

    /**
     * @brief Finds the index of a vertex by its data.
     * @param in The data of the vertex.
     * @return The index of the vertex, or -1 if not found.
     */
    int findVertexIdx(const T &in) const;

};

/**
 * @brief Creates a copy of a given graph.
 * @param g The graph to copy.
 * @return A pointer to the new copied graph.
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