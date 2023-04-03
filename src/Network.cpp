//
// Created by José Pedro Soares de Oliveira on 28/03/2023.
//

#include "../include/Network.h"

const string &Network::getStationA() const {
    return stationA;
}
const string &Network::getStationB() const {
    return stationB;
}
const double Network::getCapacity() const {
    return capacity;
}
const string &Network::getService() const {
    return service;
}

void Network::setStationA(const std::string stationA) {
    this->stationA = stationA;
}
void Network::setStationB(const std::string stationB) {
    this->stationB = stationB;
}
void Network::setCapacity(const double capacity) {
    this->capacity = capacity;
}
void Network::setService(const std::string service) {
    this->service = service;
}
bool Network::operator<(const Network& network2) const{
    if(stationA==network2.stationA){
        return stationB<network2.stationB;
    }
    return stationA<network2.stationA;
}

bool Network::operator==(const Network& a) const{
    return (stationA == a.getStationA() && stationB == a.getStationB() &&
            capacity == a.getCapacity() && service == a.getService());
}
