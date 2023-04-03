//
// Created by USER on 12/03/2023.
//

#include "../include/Menu.h"
#include <sstream>
#include <unordered_set>
#include <iostream>
#include "../data_structures/Graph.h"
#include <vector>


using namespace std;
Menu::Menu() {
    db.loadStationInfo();
    db.loadNetworkInfo();
}
void Menu::init() {
    while (true){
        cout << "--------------------------------------------------------\n";
        cout << "|      Welcome to the Railway Network Management       |\n";
        cout << "|                                                      |\n";
        cout << "| 1 - Show Station info                                |\n";
        cout << "| 2 - Graph info                                       |\n";
        cout << "| 3 - Calculate the maximum number of trains that can  |\n";
        cout << "| simultaneously travel between two specific stations. |\n";
        cout << "| 4 -                                                  |\n";
        cout << "|                                                      |\n";
        cout << "| 9 - Settings                                         |\n";
        cout << "| 0 - Exit                                             |\n";
        cout << "--------------------------------------------------------\n";

        int opt;
        cout << "\nOption: ";
        cin >> opt;

        switch (opt) {
            case 1:
                db.stationInfo("Porto Campanhã");
                break;
            case 2:
                break;
            case 3:
                db.maxFLow();
                break;
        }

    }
}

