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
#include "../include/Database.h"
#include "../include/Station.h"
#include "../include/Network.h"


class Hash{
    public:
        size_t operator()(const Network& n)const{
            return n.getStationA().length() + n.getStationB().length() + n.getService().length() + n.getCapacity();
        }

};
class Database{
public:
    Database();
    void loadStationInfo();
    void loadNetworkInfo();
    void stationInfo(std::string name);
private:
    Graph trainNetwork;
    std::set<Station> stationsSet;
    std::set<Network> networkSet;
    unordered_map<std::string,Station> stations;
    unordered_map<Network,double,Hash> networks;
};


#endif //DA_PROJETO_DATABASE_H
