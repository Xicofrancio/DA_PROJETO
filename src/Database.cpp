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
    ifstream station("csv/stations.csv");

    if (station.is_open()) {
        int count = 0;
        string line, name, district, municipality, township, linestations, throwaway;
        getline(station, throwaway);
        while (getline(station, line)) {
            stringstream sep(line);
            getline(sep, name, ',');
            getline(sep, district, ',');
            getline(sep, municipality, ',');
            getline(sep, township, ',');
            getline(sep, linestations, '\n');
            Station* station = new Station(name, district, municipality, township, linestations);
            stationsSet.insert(*station);
            trainNetwork.addVertex(name);
            count++;
        }
    }else{
            cout << "stations.csv file not found in csv folder!";
        }


    }


void Database::readNetwork() {
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
void Database::loadNetworkInfo() {

    string line;
    int network_count = 0;
    std::ifstream networkFile;
    networkFile.open("../resources/network.csv");
    if (!networkFile.is_open()) {
        cout << "File not found\n";
        return;
    }

    getline(networkFile, line);
    while (getline(networkFile, line)) {
        //row.clear();
        string stationA, stationB, capacity, service;
        istringstream iss(line);
        getline(iss, stationA, ',');
        getline(iss, stationB, ',');
        getline(iss, capacity, ',');
        getline(iss, service, '\0');

        Network* network = new Network(stationA, stationB, stoi(capacity), service);
        networkSet.insert(*network);

    }
    networkFile.close();
}

void Database::stationInfo(std::string name) {
<<<<<<< HEAD
    vector<Vertex*> vrtex = trainNetwork.getVertexSet();
    for(auto f: vrtex){
        cout << "Nome: " << f->getName() << endl;
    }/*
    for(auto f: stations){
=======
    for(auto f: stationsSet){
>>>>>>> d04f444d2ed484cde13d01202b1be75583d91f71
        if(f.getName()==name){
            cout << "Nome: " << f.getName() << endl << "Distrito: " << f.getDistrict() << endl << "Municipio: " << f.getMunicipality() << endl << "Township: " << f.getTownship() << endl << "Line: " << f.getLine() << endl;
        }
    }*/
}