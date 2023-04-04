//
// Created by USER on 12/03/2023.
//

#include "../include/Database.h"



using namespace std;

Database::Database() = default;

void Database::loadStationInfo() {
    string name, district, municipality, township, l, line;
    int count = 0;
    ifstream in;
    in.open("../csv/stations.csv");
    if (!in.is_open()) {
        cout << "Impossivel abrir ficheiro";
    }
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        count++;
        getline(iss, name, ',');
        getline(iss, district, ',');
        getline(iss, municipality, ',');
        getline(iss, township, ',');
        getline(iss, l);
        Station a = Station(name, district, municipality, township, l);
        auto it = stations.find(name);
        if (it == stations.end()) {
            stations.emplace(name, a);
            trainNetwork.addVertex(a);
        }

    }
}

void Database::loadNetworkInfo() {
    int capacity;
    string staA, staB, service, line;
    double w = 0;
    ifstream in;
    in.open("../csv/network.csv");
    if(!in.is_open()){
        cout << "Impossivel abrir ficheiro";
    }
    getline(in, line);
    while(getline(in,line)) {
        istringstream iss(line);
        getline(iss, staA, ',');
        getline(iss, staB, ',');
        iss >> capacity;
        iss.ignore(1);
        getline(iss, service, ',');
        Network a  = Network(staA, staB, capacity, service);
        pair<int,string> weight = make_pair(capacity, service);
        auto iterator = networks.find(a);
        if(iterator == networks.end()){
            networks.emplace(a,w);
            auto iterator2 = stations.find(staA);
            auto iterator3 = stations.find(staB);
            trainNetwork.addBidirectionalEdge(iterator2->second,iterator3->second, capacity, service);
        }

    }
}

void Database::menu() {
    while (true){
        cout << "--------------------------------------------------------\n";
        cout << "|      Welcome to the Railway Network Management       |\n";
        cout << "|                                                      |\n";
        cout << "| 1 - Show Station info                                |\n";
        cout << "| 2 - Graph info                                       |\n";
        cout << "| 3 - Calculate the maximum number of trains that can  |\n";
        cout << "| simultaneously travel between two specific stations. |\n";
        cout << "| 4 - Calculate pairs of stations that require the     |\n";
        cout << "| most amount of trains.                               |\n";
        cout << "| 5 - Subgraph                                         |\n";
        cout << "| 9 - Settings                                         |\n";
        cout << "| 0 - Exit                                             |\n";
        cout << "--------------------------------------------------------\n";

        int opt;
        cout << "\nOption: ";
        cin >> opt;

        switch (opt) {
            case 1:
                stationInfo("Faro");
                break;
            case 2:
                break;
            case 3:
                maxFLow();
                break;
            case 4:
                mostAmountTrains();
                break;
            case 5:
                subGraph();
                break;
            default:
                cout << "Invalid input!" << endl;
                break;
        }

    }
}

void Database::subGraph(){
    vector<Edge *> deleteEdge;

    while (true) {
        cout << "--------------------------------------------------------\n";
        cout << "|                                                      |\n";
        cout << "| 1 - Which segments would you like to remove?         |\n";
        cout << "| 2 - Calculate the maximum number of trains that can  |\n";
        cout << "| simultaneously travel between two specific stations. |\n";
        cout << "| 3 - Report on the top-k most affected stations.      |\n";
        cout << "| 4 - Undo changes and go back.                        |\n";
        cout << "| 9 - Settings                                         |\n";
        cout << "| 0 - Exit                                             |\n";
        cout << "--------------------------------------------------------\n";

        int opt;
        cout << "\nOption: ";
        cin >> opt;


        if (opt == 1) {
            string s1, s2;
            cin.ignore(1, '\n');
            cout << "Enter the first station: ";
            getline(cin, s1);

            cout << "Enter the second station: ";
            getline(cin, s2);

            Vertex *s = trainNetwork.findVertexName(s1);
            Vertex *t = trainNetwork.findVertexName(s2);

            Edge *edge = trainNetwork.removeBidirectionalEdge(s, t);
            if (edge != nullptr) {
                deleteEdge.push_back(edge);
            }
        } else if (opt == 2) {
            maxFLow();
        } else if (opt == 3) {
            cout << "Not implemented" << endl;
        } else if (opt == 4) {
            for (Edge *edge: deleteEdge) {
                Station s1 = edge->getOrig()->getStation();
                Station s2 = edge->getDest()->getStation();
                trainNetwork.addBidirectionalEdge(s1, s2, edge->getWeight(), edge->getService());
                delete edge;
            }
            menu();
        }
        else{
            cout << "Invalid input!" << endl;
        }

    }

}

void Database::stationInfo(std::string name) {

    vector<Vertex*> vertex = trainNetwork.getVertexSet();
    for(auto f: vertex){
        cout << "Nome: " << f->getStation().getName() << endl;
    }
}

void Database::maxFLow() {
    string s1, s2;
    cin.ignore(1, '\n');
    cout << "Enter the first station: ";
    getline(cin, s1);

    cout << "Enter the second station: ";
    getline(cin,s2);

    Vertex* s = trainNetwork.findVertexName(s1);
    Vertex* t = trainNetwork.findVertexName(s2);

    int max = trainNetwork.edmondsKarp(s,t);
    cout << "The maximum number of trains that can simultaneously travel between " <<
    s1 << " and " << s2 << " is " << max << ".\n";


}

vector<pair<Station,Station>> Database::mostAmountTrains(){
    int max = 0;
    vector<pair<Station,Station>> result;
    for(auto vertex: trainNetwork.getVertexSet()) vertex->setVisited(false);
    for(auto vertex: trainNetwork.getVertexSet()){
        vertex->setVisited(true);
        for(auto edge: vertex->getAdj()){
            if(edge->getWeight() > max && !(edge->getDest()->isVisited())){
                result.clear();
                max = edge->getWeight();
                result.push_back(make_pair(edge->getOrig()->getStation(),edge->getDest()->getStation()));
                continue;
            }
            if(edge->getWeight() == max && !(edge->getDest()->isVisited())){
                result.push_back(make_pair(edge->getOrig()->getStation(),edge->getDest()->getStation()));
                continue;
            }
            edge->getDest()->setVisited(true);
        }
    }

    cout << "The pairs of stations that take the most of trains are: " << endl;
    for (auto it = result.begin(); it != result.end(); it++ ){
        cout << it->first.getName() << " and " << it->second.getName() << endl;
    }
    return result;
}

