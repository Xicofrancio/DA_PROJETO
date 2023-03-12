//
// Created by USER on 12/03/2023.
//

#include "../include/Menu.h"
#include <sstream>
#include <iostream>

using namespace std;

void Menu::init() {
    while (true){
        cout << "--------------------------------------------------------\n";
        cout << "|      Welcome to the Railway Network Management       |\n";
        cout << "|                                                      |\n";
        cout << "| 1 - Show Station info                                |\n";
        cout << "| 2 -                                                  |\n";
        cout << "| 3 -                                                  |\n";
        cout << "| 4 -                                                  |\n";
        cout << "|                                                      |\n";
        cout << "| 9 - Settings                                         |\n";
        cout << "| 0 - Exit                                             |\n";
        cout << "--------------------------------------------------------\n";

        char opt;
        while(true) {
            std::cout << "\nOption: ";
            std::cin >> opt;
            if(opt <= '4' && opt >= '0' || opt == '9')
                break;
            std::cout << "Not a valid option, please choose another.\n";
        }



    }
}

