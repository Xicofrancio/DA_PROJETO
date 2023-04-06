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
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

#include "VertexEdge.h"

class Graph {
public:
    ~Graph();

    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(Station station2) const;
    Vertex *findVertexName(const string &station2) const;

    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Station &station2);
    bool removeVertex(Station &station2);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(Station &sourc,Station &dest, double w, const std::string &service);
    bool addBidirectionalEdge(Station &sourc, Station &dest, double w, const std::string &service);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;


    void testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
    void augmentFlow(Vertex *s, Vertex *t, double f);
    bool dijkstra(std::string& source, std::string& dest);
    void printPath(Station* orig, Station* dest);
    double minResidual(Vertex *s, Vertex *t);
    bool augmentingPath(Vertex *s, Vertex *t);
    double minResidualCapacity(Station* source, Station* destiny);
    double optimalCostTrains(const std::string& source, const std::string& destiny);
    int edmondsKarp(Vertex* s, Vertex* t);
    bool findAugmentingPath(Vertex *source, Vertex *dest,string municip = "",string district = "") const;
    int edmondsKarp(const string &source,const string &dest, string municip = "",string district = "") const;
    double edmondsKarpCost(Station* sourceStation, Station* destinyStation);
    std::pair<double,double> minResidualCapacityCost(Station* source, Station* destiny);
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