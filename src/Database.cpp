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
    for(auto f: stationsSet){
        if(f.getName()==name){
            cout << "Nome: " << f.getName() << endl << "Distrito: " << f.getDistrict() << endl << "Municipio: " << f.getMunicipality() << endl << "Township: " << f.getTownship() << endl << "Line: " << f.getLine() << endl;
        }
    }
}