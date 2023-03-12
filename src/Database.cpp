//
// Created by USER on 12/03/2023.
//

#include <iostream>
#include "../include/Database.h"
#include "../include/Station.h"

using namespace std;

unordered_map<int, Station> Database::loadStationInfo() {
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
            count++;
            id++;
        }return stationHash;
    }else{
            cout << "stations.csv file not found in csv folder!";
        }


    }
