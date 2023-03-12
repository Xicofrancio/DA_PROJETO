//
// Created by USER on 12/03/2023.
//

#ifndef DA_PROJETO_STATION_H
#define DA_PROJETO_STATION_H


#include <string>

class Station {
public:
    const std::string &getName() const;
    const std::string &getDistrict() const;
    const std::string &getMunicipality() const;
    const std::string &getTownship() const;
    const std::string &getLine() const;
    void setName(const std::string &name);
    void setDistrict(const std::string &district);
    void setMunicipality(const std::string &municipality);
    void setTownship(const std::string &township);
    void setLine(const std::string &line);
private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;
};


#endif //DA_PROJETO_STATION_H
