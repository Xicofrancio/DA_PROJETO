//
// Created by USER on 22/03/2023.
//

#ifndef DA_PROJETO_NETWORK_H
#define DA_PROJETO_NETWORK_H

#include <string>

class Network {
private:
    std::string stationA;
    std::string stationB;
    int capacity;
    std::string service;
public:
    Network(std::string stationA, std::string stationB, int capacity, std::string service) :
        stationA(stationA), stationB(stationB), capacity(capacity), service(service){};
    const std::string &getStationA() const;
    const std::string &getStationB() const;
    const int &getCapacity() const;
    const std::string &getService() const;
    void setSrc(const std::string stationA);
    void setDest(const std::string stationB);
    void setCapacity(const int capacity);
    void setService(const std::string service);
    bool operator==(const Network& a) const;
};


#endif //DA_PROJETO_NETWORK_H
