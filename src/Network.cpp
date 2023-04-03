//
// Created by USER on 22/03/2023.
//

#include "../include/Network.h"


std::string const &Network::getStationA() const{
    return stationA;
}

std::string const &Network::getStationB() const{
    return stationB;
}

int const &Network::getCapacity() const{
    return capacity;
}

std::string const &Network::getService() const{
    return service;
}

void Network::setSrc(const std::string stationA) {
    this->stationA = stationA;
}

void Network::setDest(const std::string stationB) {
    this->stationB = stationB;
}

void Network::setCapacity(const int capacity) {
    this->capacity = capacity;
}

void Network::setService(const std::string service) {
    this->service =service;
}

bool Network::operator==(const Network& a) const{
    return (stationA == a.getStationA() && stationB == a.getStationB() &&
            capacity == a.getCapacity() && service == a.getService());
}