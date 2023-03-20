//
// Created by USER on 12/03/2023.
//

#ifndef DA_PROJETO_DATABASE_H
#define DA_PROJETO_DATABASE_H

#include "../include/Station.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "../data_structures/Graph.h"
#include <set>


class Database {
public:
    void loadStationInfo();
    void readNetwork();
    void stationInfo(std::string name);
private:
    Graph trainNetwork;
    std::set<Station> stations;

};


#endif //DA_PROJETO_DATABASE_H
