//
// Created by USER on 22/03/2023.
//

#include "../include/Network.h"

/// @brief This function gets the network source station
/// @note T = O(1)
std::string const &Network::getStationA() const{
    return stationA;
}

/// @brief This function gets the network destination station
/// @note T = O(1)
std::string const &Network::getStationB() const{
    return stationB;
}

/// @brief This function returns the network capacity
/// @note T = O(1)
int const &Network::getCapacity() const{
    return capacity;
}

/// @brief This function returns the network service
/// @note T = O(1)
std::string const &Network::getService() const{
    return service;
}

/// @brief This function sets the network source station
///@param source station name to be set
/// @note T = O(1)
void Network::setSrc(const std::string stationA) {
    this->stationA = stationA;
}

/// @brief This function sets the network destinaton station
///@param destination station name to be set
/// @note T = O(1)
void Network::setDest(const std::string stationB) {
    this->stationB = stationB;
}

/// @brief This function sets the network capacity
///@param capacity to be set
/// @note T = O(1)
void Network::setCapacity(const int capacity) {
    this->capacity = capacity;
}

/// @brief This function sets the network service
///@param service to be set
/// @note T = O(1)
void Network::setService(const std::string service) {
    this->service =service;
}

/// @brief This function compares if two networks are the same
/// @note T = O(1)
bool Network::operator==(const Network& a) const{
    return (stationA == a.getStationA() && stationB == a.getStationB() &&
            capacity == a.getCapacity() && service == a.getService());
}