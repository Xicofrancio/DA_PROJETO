//
// Created by José Pedro Soares de Oliveira on 28/03/2023.
//

#ifndef DA_PROJETO_NETWORK_H
#define DA_PROJETO_NETWORK_H
#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Network {
public:
    Network(string stationA, string stationB);
    Network(string stationA, string stationB, double capacity, string service);
    bool operator<(const Network& network2) const;

    const string getStationA() const;
    const string getStationB() const;
    const double getCapacity() const;
    const string getService() const;

    void setStationA(const string stationA);
    void setStationB(const string stationB);
    void setCapacity(const double capacity);
    void setService(const string service);

private:
    string stationA_;
    string stationB_;
    double capacity_;
    string service_;
};


#endif //DA_PROJETO_NETWORK_H
