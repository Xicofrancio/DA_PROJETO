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


class Database {
public:
    std::unordered_map<int, Station> loadStationInfo();
    void readNetwork();
};


#endif //DA_PROJETO_DATABASE_H
