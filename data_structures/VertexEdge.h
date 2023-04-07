// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"
#include "../include/Station.h"

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(Station station1);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    Station getStation() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;

    std::vector<Edge *> getIncoming() const;
    int getId() const;
    std::vector<string> getPathForCost();
    void setId(int id);
    void setStation(Station station2);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);

    Edge * addEdge(Vertex *dest, double w, const string& service, int cost);
    bool removeEdge(Station dest);
    void removeOutgoingEdges();
    std::vector<Edge*> getOutgoing(Vertex* v) const;
    friend class MutablePriorityQueue<Vertex>;
    int getCost() const;
    void setCost(int cost);
    void addPathForCost(string basicString);

    void setPathForCost(vector<string> vector1);

protected:
    Station station;                // identifier
    std::vector<Edge *> adj;  // outgoing edges
    std::vector<string> pathcost;
    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    int cost = std::numeric_limits<int>::max();
    int id;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w, const string& service, int cost);

    Vertex * getDest() const;
    int getWeight() const;
    string getService() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    int getFlow() const;
    double getCost() const;
    void setCost(double cost);
    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex * dest; // destination vertex
    int weight; // edge weight, can also be used for capacity
    string service;

    // auxiliary fields
    bool selected = false;
    int cost;
    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    int flow; // for flow-related problems
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */