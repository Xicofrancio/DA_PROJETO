//
// Created by USER on 22/03/2023.
//

#ifndef DA_PROJETO_NETWORK_H
#define DA_PROJETO_NETWORK_H

#include <string>

class NetWork {
private:
    std::string src;
    std::string dest;
    int capacity;
    std::string service;
public:
    const std::string &getSrc() const;
    const std::string &getDest() const;
    const int &getCapacity() const;
    const std::string &getService() const;
    void setSrc(const std::string src);
    void setDest(const std::string dest);
    void setCapacity(const int capacity);
    void setService(const std::string service);
};


#endif //DA_PROJETO_NETWORK_H
