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
Vertex * Graph::findVertex(Station station) const {
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
            return true;
            break;
        }
    }
    return false;
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

double Graph::minResidualCapacity(Station* source, Station* destiny) {
    double minResidualCapacity = INT_MAX;
    for (auto station = destiny; station != source;) {
        Vertex* s = findVertex(*station);
        auto railway = s->getPath();
        if (railway->getDest() == findVertex(*station)) {
            double res = railway->getWeight() - railway->getFlow();
            minResidualCapacity = std::min(minResidualCapacity, res);
            Station station = railway->getOrig()->getStation();
        }
        else {
            double es = railway->getFlow();
            minResidualCapacity = std::min(minResidualCapacity, es);
            Station station = railway->getDest()->getStation();
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
        auto result = minResidualCapacity(sourceStation, destinyStation);
        minCost += result;
        Vertex* a = findVertex(*sourceStation);
        Vertex* d = findVertex(*destinyStation);
        double res = result;
        augmentFlow(a, d, res);

    }

    return minCost;
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


void Graph::augmentFlow(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        } else {
            e->setFlow(flow - f);
            v = e->getDest();
        }}}

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

bool Graph::dijkstra(std::string& source, std::string& dest) {

    std::priority_queue<Vertex *> q;
    for (auto *v: vertexSet) {
        v->setVisited(false);
        v->setDist(INT32_MAX);
        v->setPath(nullptr);
    }
    Vertex *a = findVertexName(source);
    a->setDist(0);
    q.push(a);

    while (!q.empty()) {
        Vertex *top = q.top();
        q.pop();

        if (top->isVisited()) continue;
        top->setVisited(true);

        if (top->getStation().getName() == dest) {
            break;
        }
        for (Edge *railway: top->getOutgoing(top)) {

            Vertex * contender = findVertex(railway->getDest()->getStation());
            if (contender->isVisited()) continue;

            double cost = (railway->getService() == "STANDARD" ? 2 : 4);
            double residualCapacity = railway->getWeight()-railway->getFlow();

            if (contender->getDist() > top->getDist() + cost && residualCapacity>0) {
                contender->setDist(top->getDist() + cost);
                contender->setPath(railway);
                q.push(contender);
            }
        }
    }

    if (!findVertexName(dest)->isVisited()) return false;
    return true;
}


void Graph::printPath(Station* orig, Station* dest){
    Vertex* it = findVertex(*dest);
    Station st = it->getStation();
    if(&st !=  orig){
        Station stt = it->getPath()->getOrig()->getStation();
        printPath(orig, &stt);
    }
    Station sttt = it->getStation();
    if(&sttt == orig){
        std::cout << it->getStation().getName();
    }

    else {
        std::cout << "->" << it->getStation().getName();
    }
}

double Graph::optimalCostTrains(const std::string& source, const std::string& destiny){
    for (auto v: vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    Vertex* s = findVertexName(source);
    Vertex* d = findVertexName(destiny);
    auto sourceStation = s->getStation();
    auto destinyStation = d->getStation();


    if(sourceStation == destinyStation){
        return -3;
    }

    double minCost = std::numeric_limits<double>::infinity();
    while(dijkstra(const_cast<std::string &>(sourceStation.getName()),
                   const_cast<std::string &>(destinyStation.getName()))){
        printPath(&sourceStation, &destinyStation);
        auto residualCapacity = minResidualCapacity(&sourceStation, &destinyStation);
        augmentFlow(findVertex(sourceStation), findVertex(destinyStation), residualCapacity);
        minCost = std::min(minCost, findVertex(destinyStation)->getDist()*residualCapacity);
        std::cout << ". The cost of this path is " << findVertex(destinyStation)->getDist()*residualCapacity << "€;\n";
    }

    return minCost;
}

