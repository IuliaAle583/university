//
// Created by mariasiu alexandra on 14.06.2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
#include <vector>
#include <algorithm>

class Biologist {
private:
    std::string name;
    std::vector<std::string> species;

public:
    Biologist(const std::string& name, const std::vector<std::string>& species)
        : name(name), species(species) {}

    std::string getName() const { return name; }
    const std::vector<std::string>& getSpecies() const { return species; }

    bool studiesSpecies(const std::string& sp) const {
        return std::find(species.begin(), species.end(), sp) != species.end();
    }
};

class Bacterium {
private:
    std::string name;
    std::string species;
    int size;
    std::vector<std::string> diseases;

public:
    Bacterium(const std::string& name, const std::string& species, int size, const std::vector<std::string>& diseases)
        : name(name), species(species), size(size), diseases(diseases) {}

    std::string getName() const { return name; }
    std::string getSpecies() const { return species; }
    int getSize() const { return size; }
    const std::vector<std::string>& getDiseases() const { return diseases; }

    void setSpecies(const std::string& s) { species = s; }
    void setSize(int s) { size = s; }
    void setName(const std::string& n) { name = n; }
    void setDiseases(const std::vector<std::string>& d) { diseases = d; }

    void addDisease(const std::string& d) {
        diseases.push_back(d);
    }
};

#endif // DOMAIN_H
