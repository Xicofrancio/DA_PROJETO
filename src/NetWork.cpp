//
// Created by USER on 22/03/2023.
//

#include "../include/NetWork.h"


std::string const &NetWork::getSrc() const{
    return src;
}

std::string const &NetWork::getDest() const{
    return dest;
}

int const &NetWork::getCapacity() const{
    return capacity;
}

std::string const &NetWork::getService() const{
    return service;
}

void NetWork::setSrc(const std::string src) {
    this->src = src;
}

void NetWork::setDest(const std::string dest) {
    this->dest = dest;
}

void NetWork::setCapacity(const int capacity) {
    this->capacity = capacity;
}

void NetWork::setService(const std::string service) {
    this->service =service;
}