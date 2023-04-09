//
// Created by USER on 12/03/2023.
//

#include "../include/Station.h"

/// @brief This function returns the station name
/// @note T = O(1)
const std::string &Station::getName() const {
    return name;
}

/// @brief This function returns the station district name
/// @note T = O(1)
const std::string &Station::getDistrict() const {
    return district;
}

/// @brief This function returns the station line
/// @note T = O(1)
const std::string &Station::getLine() const {
    return line;
}

/// @brief This function returns the station municipality
/// @note T = O(1)
const std::string &Station::getMunicipality() const {
    return municipality;
}

/// @brief This function returns the station township
/// @note T = O(1)
const std::string &Station::getTownship() const {
    return township;
}

/// @brief This function sets the station name
/// @note T = O(1)
void Station::setName(const std::string &name) {
    this->name = name;
}

/// @brief This function sets the station district
/// @note T = O(1)
void Station::setDistrict(const std::string &district) {
    this->district = district;
}

/// @brief This function sets the station line
/// @note T = O(1)
void Station::setLine(const std::string &line) {
    this->line = line;
}

/// @brief This function sets the station municipality
/// @note T = O(1)
void Station::setMunicipality(const std::string &municipality) {
    this->municipality = municipality;
}

/// @brief This function sets the station township
/// @note T = O(1)
void Station::setTownship(const std::string &township) {
    this->township = township;
}

/// @brief This function compares two stations by name
/// @note T = O(1)
bool Station::operator<(const Station &s1) const {
    if(this->name < s1.name) return true;
    return false;

}

/// @brief This function checks if two stations are identical
/// @return true if the condition verifies
/// @return false otherwise
/// @note T = O(1)
bool Station::operator==(const Station &s1) const {
    return s1.getName() == name && s1.getDistrict() == district &&
           s1.getLine() == line && s1.getMunicipality() == municipality &&
           s1.getTownship() == township;
}