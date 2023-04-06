//
// Created by USER on 12/03/2023.
//

#include "../include/Station.h"


const std::string &Station::getName() const {
    return name;
}

const std::string &Station::getDistrict() const {
    return district;
}

const std::string &Station::getLine() const {
    return line;
}

const std::string &Station::getMunicipality() const {
    return municipality;
}

const std::string &Station::getTownship() const {
    return township;
}

void Station::setName(const std::string &name) {
    this->name = name;
}

void Station::setDistrict(const std::string &district) {
    this->district = district;
}

void Station::setLine(const std::string &line) {
    this->line = line;
}

void Station::setMunicipality(const std::string &municipality) {
    this->municipality = municipality;
}

void Station::setTownship(const std::string &township) {
    this->township = township;
}


bool Station::operator<(const Station &s1) const {
    if(this->name < s1.name) return true;
    return false;

}

bool Station::operator==(const Station &s1) const {
    return s1.getName() == name && s1.getDistrict() == district &&
           s1.getLine() == line && s1.getMunicipality() == municipality &&
           s1.getTownship() == township;
}

