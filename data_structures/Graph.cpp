// By: Gonçalo Leão

#include "Graph.h"
#include "MutablePriorityQueue.h"

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(Station &station) const {
    for (auto v : vertexSet)
        if (v->getStation() == station)
            return v;
    return nullptr;
}

Vertex * Graph::findVertexName(string &name) const {
    for (auto v : vertexSet)
        if (v->getStation().getName() == name)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(Station &station) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getStation() == station)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(Station &station) {
    if (findVertex(station) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(station));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(Station &sourc, Station &dest, double w, const std::string &service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w,service);
    return true;
}

bool
Graph::addBidirectionalEdge(Station &sourc,Station &dest, double w, const std::string &service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w,service);
    auto e2 = v2->addEdge(v1, w,service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}


void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

void Graph::testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Graph::augmentingPath(Vertex *s, Vertex *t) {
    for(auto vertex : vertexSet) {
        vertex->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while( ! q.empty() && ! t->isVisited()) {
        auto vertex = q.front();
        q.pop();
        for(auto e: vertex->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for(auto e: vertex->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}
double Graph::minResidual(Vertex *s, Vertex *t) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Graph::augmentFlow(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

int Graph::edmondsKarp(Vertex *s, Vertex *t) {
    for(auto vertex: vertexSet){
        for(auto edge: vertex->getAdj()){
            edge->setFlow(0);
        }
    }
    while(augmentingPath(s,t)){
        double f = minResidual(s,t);
        augmentFlow(s,t,f);
    }
    int max = 0;
    for(Edge* e : s->getAdj()){
        max += e->getFlow();
    }
    return max;
}

Edge* Graph::removeBidirectionalEdge(Vertex *s, Vertex *t) {
    Edge* res = nullptr;
    for (Edge* e : s->getAdj()){
        if (e->getDest() == t){
            res = new Edge(*e);
        }
    }
    if (res == nullptr) return nullptr;
    if (s->removeEdge(t->getStation()) && t->removeEdge(s->getStation())) return res;
    else return nullptr;
}



void Graph::dijkstraShortestPath(Graph &graph, Vertex *startVertex) {
    for (auto v : graph.vertexSet) {
        v->setDist(INF);
        v->setPath(nullptr);
    }

    MutablePriorityQueue<Vertex> queue;
    startVertex->setDist(0);
    queue.insert(startVertex);

    while (!queue.empty()) {
        auto vertex = queue.extractMin();
        vertex->setVisited(true);

        for (auto edge : vertex->getAdj()) {
            auto dest = edge->getDest();
            if (!dest->isVisited()) {
                auto newDist = vertex->getDist() + edge->getWeight();
                if (newDist < dest->getDist()) {
                    dest->setDist(newDist);
                    dest->setPath(edge);
                    if (queue.find(dest) != queue.end()) {
                        queue.decreaseKey(dest);
                    } else {
                        queue.insert(dest);
                    }
                }
            }
        }
    }
}
