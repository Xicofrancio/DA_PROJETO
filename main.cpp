#include <iostream>
#include "include/Database.h"

using namespace std;

int main() {
    Database d;
    d.loadStationInfo();
    d.loadNetworkInfo();
    d.menu();
    return 0;
}
