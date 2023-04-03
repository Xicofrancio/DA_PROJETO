//
// Created by USER on 12/03/2023.
//

#include "../include/Database.h"



using namespace std;

Database::Database(){
    loadStationInfo();
    loadNetworkInfo();
}
void Database::loadStationInfo() {
    string name, district, municipality, township, l, line;
    int count = 0;
    ifstream in;
    in.open("csv/stations.csv");
    if (!in.is_open()) {
        cout << "Impossivel abrir ficheiro";
    }
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        count++;
        getline(iss, name, ',');
        getline(iss, district, ',');
        getline(iss, municipality, ',');
        getline(iss, township, ',');
        getline(iss, l);
        Station a = Station(name, district, municipality, township, l);
        auto it = stations.find(name);
        if (it == stations.end()) {
            stations.emplace(name, a);
            trainNetwork.addVertex(a);

        }

    }
}

void Database::loadNetworkInfo() {
    int capacity;
    string staA, staB, service, line;
    double w = 0;
    ifstream in;
    in.open("csv/network.csv");
    if(!in.is_open()){
        cout << "Impossivel abrir ficheiro";
    }
    getline(in, line);
    while(getline(in,line)) {
        istringstream iss(line);
        getline(iss, staA, ',');
        getline(iss, staB, ',');
        iss >> capacity;
        iss.ignore(1);
        getline(iss, service, ',');
        Network a  = Network(staA, staB, capacity, service);
        pair<int,string> weight = make_pair(capacity, service);
        auto iterator = networks.find(a);
        if(iterator == networks.end()){
            networks.emplace(a,w);
            auto iterator2 = stations.find(staA);
            auto iterator3 = stations.find(staB);
            trainNetwork.addBidirectionalEdge(iterator2->second,iterator3->second, capacity, service);
        }

    }
}

void Database::stationInfo(std::string name) {

    vector<Vertex*> vrtex = trainNetwork.getVertexSet();
    for(auto f: vrtex){
        cout << "Nome: " << f->getStation().getName() << endl;
    }
}

void Database::maxFLow() {
    string s1, s2;
    cout << "Enter the first station: ";
    cin >> s1;
    cout << "Enter the first station: ";
    cin >> s2;

    Vertex* s = trainNetwork.findVertex(s1);
    Vertex* t = trainNetwork.findVertex(s2);

    int max = trainNetwork.edmondsKarp(s,t);
    cout << "The maximum number of trains that can simultaneously travel between " <<
    s << " and " << t << " is " << max << ".\n";


}