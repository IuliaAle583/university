#pragma once

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Biologist {
private:
    string name;
    vector<string> species;

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
    string name;
    string species;
    int size;
    vector<string> diseases;

public:
    Bacterium(const std::string& name, const std::string& species, int size, const std::vector<std::string>& diseases)
        : name(name), species(species), size(size), diseases(diseases) {}

    void setSpecies(const std::string& s) { species = s; }
    void setSize(int s) { size = s; }
    void setName(const std::string& n) { name = n; }
    void setDiseases(const std::vector<std::string>& d) { diseases = d; }

    std::string getName() const { return name; }
    std::string getSpecies() const { return species; }
    int getSize() const { return size; }
    const std::vector<std::string>& getDiseases() const { return diseases; }
    void addDisease(const std::string& d) {
        diseases.push_back(d);
    }
};

