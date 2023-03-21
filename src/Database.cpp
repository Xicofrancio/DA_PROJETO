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
    Graph g;
    ifstream infile("csv/network.csv");
    string line;
    getline(infile,line); // Skip First Line

    while(getline(infile,line)){

        istringstream iss(line);
        string substring;
        vector<string> substrings{};

        while(getline(iss, substring, ',')){
            substrings.push_back(substring);
        }
        g.addEdge(substrings[0], substrings[1], stoi(substrings[2]), substrings[3]);
    }
}

void Database::stationInfo(std::string name) {
    for(auto f: stations){
        if(f.getName()==name){
            cout << "Nome: " << f.getName() << endl << "Distrito: " << f.getDistrict() << endl << "Municipio: " << f.getMunicipality() << endl << "Township: " << f.getTownship() << endl << "Line: " << f.getLine() << endl;
        }
    }
}