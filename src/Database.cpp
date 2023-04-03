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
    int count = 0 ;g
    ifstream infile("csv/stations.csv");
    if(!infile.open()){
        cout << "Impossivel abrir ficheiro";
    }
    getline(in, line);
    while(getline(in,line)){
        istringstream iss(line);
        count++;
        getline(iss,name,',');
        getline(iss,district,',');
        getline(iss,municipality,',');
        getline(iss,township,',');
        getline(iss,l);
        Station a = Station(name, district, municipality, township, l);
        auto iterator = stations.find(name);
        if(iterator==stations.end()){
            stations.emplace(name,a);
            trainNetwork.addVertex(a);
        }
    }
}



void Database::loadNetworkInfo() {
    int capacity;
    string staA, staB, service, line;
    double w = 0;
    ifstream infile;
    infile.open("csv/network.csv");
    if(!infile.is_open()){
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
        if(it == networks.end()){
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
        cout << "Nome: " << f->getName() << endl;
    }/*
    for(auto f: stations){

    for(auto f: stationsSet){

        if(f.getName()==name){
            cout << "Nome: " << f.getName() << endl << "Distrito: " << f.getDistrict() << endl << "Municipio: " << f.getMunicipality() << endl << "Township: " << f.getTownship() << endl << "Line: " << f.getLine() << endl;
        }
    }*/
}