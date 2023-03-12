//
// Created by USER on 12/03/2023.
//

#ifndef DA_PROJETO_MENU_H
#define DA_PROJETO_MENU_H


#include "Database.h"
#include "../include/Station.h"
class Menu {
    Database db;
    std::unordered_map<int, Station> stations;


public:
    Menu();
    void init();
};


#endif //DA_PROJETO_MENU_H
