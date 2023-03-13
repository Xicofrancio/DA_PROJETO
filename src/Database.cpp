//
// Created by USER on 12/03/2023.
//

#include <iostream>
#include "../include/Database.h"
#include "../include/Station.h"
#include "../data_structures/Graph.h"

using namespace std;

unordered_map<int, Station> Database::loadStationInfo() {
    Graph g;
    unordered_map<int, Station> stationHash;

    ifstream stations("csv/stations.csv");

    if (stations.is_open()) {
        int count = 0,id=0;
        Station station;
        string line, name, district, municipality, township, linestations, throwaway;
        getline(stations, throwaway);
        while (getline(stations, line)) {
            stringstream sep(line);
            getline(sep, name, ',');
            getline(sep, district, ',');
            getline(sep, municipality, ',');
            getline(sep, township, ',');
            getline(sep, linestations, '\n');
            station.setName(name);
            station.setDistrict(district);
            station.setMunicipality(municipality);
            station.setTownship(township);
            station.setLine(linestations);
            stationHash[count] = station;
            g.addVertex(name);
            count++;
            id++;
        }return stationHash;
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