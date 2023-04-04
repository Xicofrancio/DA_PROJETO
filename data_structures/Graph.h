// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include "MutablePriorityQueue.h"

#include "VertexEdge.h"

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(Station &station2) const;
    Vertex *findVertexName(const string &station2) const;

    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Station &station2);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(Station &sourc,Station &dest, double w, const std::string &service);
    bool addBidirectionalEdge(Station &sourc,Station &dest, double w, const std::string &service);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;

    bool findAugmentingPath(Vertex *source, Vertex *dest) const;
    int edmondsKarp(const string &source,const string &dest) const;
    Edge* removeBidirectionalEdge(Vertex *s, Vertex *t);
    vector<pair<pair<Station,Station>,int>> mostAmountTrains();
protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(Station &statio) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */