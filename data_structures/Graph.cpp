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



int Graph::edmondsKarp(const string &source,const string &dest, string municip, string district) const{
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

    while (findAugmentingPath(s, t,municip,district)) {
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

bool Graph::findAugmentingPath(Vertex *source, Vertex *dest,string municip, string district) const {
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
            if (!w->isVisited() && e->getWeight() - e->getFlow() > 0 && (( w->getStation().getMunicipality() == municip || w->getStation().getDistrict() == district) || (municip == "" && district == ""))) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }

        for (auto e: v->getIncoming()) {
            auto w = e->getOrig();
            if (!w->isVisited() && e->getFlow() > 0 && (( w->getStation().getMunicipality() == municip || w->getStation().getDistrict() == district) || (municip == "" && district == ""))) {
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

std::pair<double,double> Graph::minResidualCapacityCost(Station* source, Station* destiny) {
    std::pair<double,double> minResidualCapacity = {0,INT_MAX};
    int price = 0;
    for (auto station = destiny; station != source;) {
        Vertex* s = findVertex(reinterpret_cast<Station &>(station));
        auto railway = s->getPath();

        if (railway->getDest()->getStation() == *station) {
            price += railway->getService()=="STANDARD" ? 2:4;
            minResidualCapacity = {price,std::min(reinterpret_cast<int &>(minResidualCapacity.second), railway->getWeight() - railway->getFlow())};
            *station = railway->getOrig()->getStation();

        }
        else {
            minResidualCapacity = {price,std::min(reinterpret_cast<int &>(minResidualCapacity.second), railway->getFlow())};
            *station = railway->getDest()->getStation();
        }
    }
    return minResidualCapacity;
}

double Graph::edmondsKarpCost(Station *sourceStation, Station *destinyStation) {
    for (auto v: vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    double minCost = 0;
    int i = 0;
    auto s = findVertexName(sourceStation->getName());
    auto t = findVertexName(destinyStation->getName());
    while (findAugmentingPath(s, t)) {
        std::cout << "Path " << i++ << std::endl;
        auto result = minResidualCapacityCost(sourceStation, destinyStation);
        minCost += result.first*result.second;
    }

    return minCost;
}

double Graph::optimalCostTrains(const std::string &source, const std::string &destiny) {
    auto sourceStation = findVertexName(source);
    auto destinyStation = findVertexName(destiny);
    if(sourceStation == nullptr){
        return -1;
    }

    if(destinyStation == nullptr){
        return -1;
    }

    if(sourceStation == destinyStation){
        return -1;
    }

    return edmondsKarpCost(reinterpret_cast<Station *>(sourceStation), reinterpret_cast<Station *>(destinyStation));
}

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

Graph::Graph(Graph* copy){
    for(auto v : copy->vertexSet){
        Station s = v->getStation();
        this->addVertex(s);
    }
    for(auto v: copy->vertexSet) for(auto e: v->getAdj()){
        Station origin = e->getOrig()->getStation();
        Station dest = e->getDest()->getStation();
        this->addBidirectionalEdge(origin,dest,e->getWeight(),e->getService());
    }
}