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
#include <unordered_map>
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
    void menu();
    void loadStationInfo();
    void loadNetworkInfo();
    void maxFLow();
    void maxTrainsminCost();
    void subGraph();
    void mostAmountTrains();
    void maximumNArriveStation();
    void largermaintenancebudget();
    void mostaffectedstations();
    int maximumNArriveStation2(string stationname);
private:
    Graph trainNetwork;
    unordered_map<std::string,Station> stations;
    unordered_map<Network,double,Hash> networks;
    void stationInfo(string name);
    vector<Edge *> deleteEdge;
};



#endif //DA_PROJETO_DATABASE_H
