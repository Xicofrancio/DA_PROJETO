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
    stations = db.loadStationInfo();
    db.readNetwork();
}
void Menu::init() {
    while (true){
        cout << "--------------------------------------------------------\n";
        cout << "|      Welcome to the Railway Network Management       |\n";
        cout << "|                                                      |\n";
        cout << "| 1 - Show Station info                                |\n";
        cout << "| 2 - Graph info                                       |\n";
        cout << "| 3 -                                                  |\n";
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
                for(auto f: stations){
                    cout << "Nome: " << f.second.getName() << " " << "Distrito: " << f.second.getDistrict() << " " << "Municipality: " << f.second.getMunicipality() << " " << "Township: " << f.second.getTownship() << " " << "Line: " << f.second.getLine() << endl;
                }
            case 2:
                Graph g;

                vector<Vertex *> vertex = g.getVertexSet();
                for(auto f: vertex){
                    cout << f->getName() << endl;
                }
        }

    }
}

