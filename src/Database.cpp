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
            int cost = 0;
            if(service == "STANDARD"){
                cost = 2;
            }else if(service == "ALFA PENDULAR"){
                cost = 4;
            }
            trainNetwork.addBidirectionalEdge(iterator2->second,iterator3->second, capacity, service, cost);


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
        cout << "| 6 - The maximum number of trains that can            |\n";
        cout << "| simultaneously arrive at a given station             |\n";
        cout << "| 7 - Calculate the maximum amount of trains that can  |\n";
        cout << "| simultaneously travel between two specific           |\n";
        cout << "| stations with minimum cost for the company           |\n";
        cout << "| 8 - Calculate where should management assign         |\n";
        cout << "| larger budgets                                       |\n";
        cout << "| 9 - Settings                                         |\n";
        cout << "| 0 - Exit                                             |\n";
        cout << "--------------------------------------------------------\n";

        int opt;
        cout << "\nOption: ";
        cin >> opt;

        switch (opt) {
            case 0:
                break;
            case 1:
                maxFLow();
                break;
            case 2:
                mostAmountTrains();
                break;
            case 3:
                largermaintenancebudget();
                break;
            case 4:
                maximumNArriveStation();
                break;
            case 5:
                //to implement
                break;
            case 6:
                subGraph();
                break;
            case 7:

                maxTrainsminCost();
                break;
            case 8:
                largermaintenancebudget();
            default:
                cout << "Invalid input!" << endl;
                break;
        }

    }
}

void Database::subGraph(){
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
            mostaffectedstations();
        } else if (opt == 4) {
            for (Edge *edge: deleteEdge) {
                Station s1 = edge->getOrig()->getStation();
                Station s2 = edge->getDest()->getStation();
                trainNetwork.addBidirectionalEdge(s1, s2, edge->getWeight(), edge->getService(), edge->getCost());
                delete edge;
            }
            menu();
        }
        else{
            cout << "Invalid input!" << endl;
            break;
        }

    }

}

/// @brief prints the station info
/// @note T = O(V)
void Database::stationInfo(std::string name) {

    vector<Vertex*> vertex = trainNetwork.getVertexSet();
    for(auto f: vertex){
        cout << "Nome: " << f->getStation().getName() << endl;
    }
}

/// @brief prints the maximum number of trains that can simultaneously travel between two specific stations
/// @note T = O(VE^2)
void Database::maxFLow() {
    string s1, s2;
    cin.ignore(1, '\n');
    cout << "Enter the first station: ";
    getline(cin, s1);

    cout << "Enter the second station: ";
    getline(cin,s2);


    int max = trainNetwork.edmondsKarp(s1,s2);
    cout << "The maximum number of trains that can simultaneously travel between " <<
    s1 << " and " << s2 << " is " << max << ".\n";


}

/// @brief prints the pairs of stations that require the most amount of trains
void Database::mostAmountTrains(){

    vector<pair<pair<Station,Station>,int>> result = trainNetwork.mostAmountTrains();

    cout << "The pairs of stations that take the most of trains are: " << endl;
    for (auto it = result.begin(); it != result.end(); it++ ){
        cout << it->first.first.getName() << " and " << it->first.second.getName() << endl;
    }
}

/// @brief prints the maximum number of trains that can simultaneously arrive at a given station
/// @note T = O(VE^2)
void Database::maximumNArriveStation(){
    string name;
    cin.ignore(1, '\n');
    cout << "Enter the station name: ";
    getline(cin,name);

    Vertex *station = trainNetwork.findVertexName(name);

    Station s = Station("s","","","","");
    trainNetwork.addVertex(s);

    for(Vertex* vertex: trainNetwork.getVertexSet()){
        if(!(vertex->getStation().getName() == name) && vertex->getAdj().size() ==1 ){
            for (auto v : trainNetwork.getVertexSet()){
                for(auto edge : v->getAdj()){
                    edge->setFlow(0);
                }
            }
            if(trainNetwork.findAugmentingPath(vertex,station)){
                Station temp = vertex->getStation();
                trainNetwork.addBidirectionalEdge(s,temp,numeric_limits<int>::max(),"",numeric_limits<int>::max());
            }
        }

    }

    int max = trainNetwork.edmondsKarp(s.getName(),name);
    cout << "The maximum number of trains that can simultaneously arrive at "<< name << " is " << max << "." << endl;
    loadStationInfo();
    loadNetworkInfo();


}

/// @brief prints the the maximum amount of trains that can simultaneously travel between two specific stations with minimum cost for the company
/// @note T = O(VE^2)
void Database::maxTrainsminCost() {
    double maxTrains;
    string s1, s2;
    cin.ignore(1, '\n');
    cout << "Enter the first station: ";
    getline(cin, s1);

    cout << "Enter the second station: ";
    getline(cin,s2);

    trainNetwork.dijkstra(s1, s2);



}

/// @brief prints where should management assign larger budgets
/// @note T = O(VE^2)
void Database::largermaintenancebudget(){
    vector<pair<string,int>> municips2;
    vector<pair<string,int>> districts2;
    vector<string> municips;
    vector<string> districts;
    int result;

    int opt;
    cout << "Enter the top-k municipalities and districts: ";
    cin >> opt;
    for(auto vertex: trainNetwork.getVertexSet()){
        string name = vertex->getStation().getName();
        string municip = vertex->getStation().getMunicipality();
        // checks if the municipality was already seen
        if(find(municips.begin(),municips.end(),municip) != municips.end()){
            continue;
        }
        municips.push_back(municip);
        for(auto vertex: trainNetwork.getVertexSet()){
            string name2 = vertex->getStation().getName();
            string municip2 = vertex->getStation().getMunicipality();
            if(municip2 == municip && name2 != name){
                // add max flow
                result += trainNetwork.edmondsKarp(name,name2,municip);
            }
        }
        municips2.push_back(make_pair(municip,result));
        result = 0;
    }
    //sort municipalities based on the sum of the maxflows
    sort(municips2.begin(), municips2.end(), [](const std::pair<string,int> &left, const std::pair<string,int> &right) {
        return left.second > right.second;
    });
    for(auto vertex: trainNetwork.getVertexSet()){
        string name = vertex->getStation().getName();
        string district = vertex->getStation().getDistrict();
        if(find(districts.begin(),districts.end(),district) != districts.end()){
            continue;
        }
        districts.push_back(district);
        for(auto vertex: trainNetwork.getVertexSet()){
            string name2 = vertex->getStation().getName();
            string district2 = vertex->getStation().getDistrict();
            if(district2 == district && name2 != name){
                result += trainNetwork.edmondsKarp(name,name2,district);
            }
        }
        districts2.push_back(make_pair(district,result));
        result = 0;
    }
    sort(districts2.begin(), districts2.end(), [](const std::pair<string,int> &left, const std::pair<string,int> &right) {
        return left.second > right.second;
    });
    cout << "Top " << to_string(opt) <<" Municipalities:" << "\n";
    for(int i = 0;i<opt;i++){
        cout << municips2[i].first;
        cout << "\n";
    }
    cout << "\n";
    cout << "Top " << to_string(opt) <<" Districts:" << "\n";
    for(int i = 0;i<opt;i++){
        cout << districts2[i].first;
        cout << "\n";
    }
    loadStationInfo();
    loadNetworkInfo();
}

/// @brief prints the top affected stations by segment failures
/// @note T = O(VE^2)
void Database::mostaffectedstations(){
    vector<pair<string,int>> vec;
    vector<Station> stat;
    int opt;
    cout << "Enter the number of stations: ";
    cin >> opt;

    for(auto v1: trainNetwork.getVertexSet()){
        if(find(stat.begin(),stat.end(),v1->getStation()) == stat.end()){
            stat.push_back(v1->getStation());
            int newflow = maximumNArriveStation2(v1->getStation().getName());
            for (Edge *edge: deleteEdge){
                Station t1 = edge->getOrig()->getStation();
                Station t2 = edge->getDest()->getStation();
                trainNetwork.addBidirectionalEdge(t1,t2,edge->getWeight(),edge->getService(),edge->getCost());
            }
            int oldflow = maximumNArriveStation2(v1->getStation().getName());
            for (Edge *edge: deleteEdge){
                trainNetwork.removeBidirectionalEdge(edge->getOrig(),edge->getDest());
            }
            int dif = oldflow-newflow;
            vec.emplace_back(make_pair(v1->getStation().getName(),dif));
        }
    }
    sort(vec.begin(), vec.end(), [](const std::pair<string,int> &left, const std::pair<string,int> &right) {
        return left.second > right.second;
    });
    cout << "Top " << to_string(opt) <<" affected stations:" << "\n";
    for(int i = 0;i<opt;i++){
        cout << vec[i].first;
        cout << "\n";
    }
}

int Database::maximumNArriveStation2(string stationname){
    Vertex *station = trainNetwork.findVertexName(stationname);

    Station s = Station("s","","","","");
    trainNetwork.addVertex(s);

    for(Vertex* vertex: trainNetwork.getVertexSet()){
        if(!(vertex->getStation().getName() == stationname) && vertex->getAdj().size() ==1 ){
            for (auto v : trainNetwork.getVertexSet()){
                for(auto edge : v->getAdj()){
                    edge->setFlow(0);
                }
            }
            if(trainNetwork.findAugmentingPath(vertex,station)){
                Station temp = vertex->getStation();
                trainNetwork.addBidirectionalEdge(s,temp,numeric_limits<int>::max(),"",numeric_limits<int>::max());
            }
        }

    }
    int max = trainNetwork.edmondsKarp(s.getName(),stationname);
    loadStationInfo();
    loadNetworkInfo();
    return max;
}