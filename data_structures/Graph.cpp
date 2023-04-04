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

Vertex * Graph::findVertexName(const string &name) const {
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

bool Graph::removeVertex(Station &station2){
    for(auto it = vertexSet.begin(); it != vertexSet.end(); it++){
        if((*it)->getStation() == station2){
            vertexSet.erase(it);
            break;
        }
    }
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
Graph::addBidirectionalEdge(Station &sourc, Station &dest, double w, const std::string &service) {
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



int Graph::edmondsKarp(const string &source,const string &dest, string municip) const{
    auto s = findVertexName(source);
    auto t = findVertexName(dest);

    if (s == nullptr || t == nullptr || s == t) {
        return -1;
    }

    for (auto v: vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    int max_flow = 0;

    while (findAugmentingPath(s, t)) {
        int pathFlow = std::numeric_limits<int>::max();

        for (auto v = t; v != s;) {
            auto e = v->getPath();
            if (e->getDest() == v) {
                pathFlow = std::min(pathFlow, e->getWeight() - e->getFlow());
                v = e->getOrig();
            } else {
                pathFlow = std::min(pathFlow, e->getFlow());
                v = e->getDest();
            }
        }

        // Update the flow in the path
        for (auto v = t; v != s;) {
            auto e = v->getPath();
            if (e->getDest() == v) {
                e->setFlow(e->getFlow() + pathFlow);
                v = e->getOrig();
            } else {
                e->setFlow(e->getFlow() - pathFlow);
                v = e->getDest();
            }
        }

        max_flow += pathFlow;
    }

    return (max_flow ? max_flow : -1);
}

bool Graph::findAugmentingPath(Vertex *source, Vertex *dest) const {
    for (auto v: vertexSet) {
        v->setVisited(false);
    }

    source->setVisited(true);
    std::queue<Vertex *> q;
    q.push(source);

    while (!q.empty() && !dest->isVisited()) {
        auto v = q.front(); q.pop();

        for (auto e: v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited() && e->getWeight() - e->getFlow() > 0 ) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }

        for (auto e: v->getIncoming()) {
            auto w = e->getOrig();
            if (!w->isVisited() && e->getFlow() > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }

    return dest->isVisited();
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



/*
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
}*/

vector<pair<pair<Station,Station>,int>> Graph::mostAmountTrains(){
    vector<pair<pair<Station,Station>,int>> max_pair;
    unordered_map<string,int> max_flow;
    int max_trains = 0;

    for (const auto &source: vertexSet) {
        for(const auto &dest: vertexSet){
            string source_n = source->getStation().getName();
            string dest_n = dest->getStation().getName();
            int count = -1;

            if(max_flow.find(source_n+dest_n) != max_flow.end()){
                count = max_flow[source_n+dest_n];
            }
            else{
                count = edmondsKarp(source_n,dest_n);

                max_flow[source_n + dest_n] = count;
                max_flow[dest_n + source_n] = count;
            }
            if(count > max_trains){
                max_pair.clear();
                max_pair.push_back(make_pair(make_pair(source->getStation(),dest->getStation()),count));
                max_trains = count;
            }
            else if(count == max_trains){
                max_pair.push_back(make_pair(make_pair(source->getStation(),dest->getStation()),count));
            }
        }
    }
    return max_pair;
}

