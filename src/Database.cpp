//
// Created by USER on 12/03/2023.
//

#include <iostream>
#include "../include/Database.h"
#include "../include/Station.h"
#include "../data_structures/Graph.h"


using namespace std;

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
            stations.insert(*station);
            trainNetwork.addVertex(name);
            count++;
        }
    }else{
            cout << "stations.csv file not found in csv folder!";
        }


    }

void Database::readNetwork() {
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

        Network network(stationA, stationB, stoi(capacity), service);
        networkSet.insert(network);

        int code_StationA = stations_code_reverse[stationA];
        int code_StationB = stations_code_reverse[stationB];
        addEdge(code_StationA, code_StationB, std::stod(capacity));
    }
    networkFile.close();
}

void Database::stationInfo(std::string name) {
    for(auto f: stations){
        if(f.getName()==name){
            cout << "Nome: " << f.getName() << endl << "Distrito: " << f.getDistrict() << endl << "Municipio: " << f.getMunicipality() << endl << "Township: " << f.getTownship() << endl << "Line: " << f.getLine() << endl;
        }
    }
}