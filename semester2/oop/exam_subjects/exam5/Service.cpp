//
// Created by mariasiu alexandra on 14.06.2025.
//

#include "Service.h"

Service::Service(Repository& r) : repo(r) {}

const std::vector<Biologist>& Service::getAllBiologists() const {
    return repo.getBiologists();
}

const std::vector<Bacterium>& Service::getAllBacteria() const {
    return repo.getBacteria();
}

std::vector<Bacterium> Service::getBacteriaForSpecies(const std::string& species) const {
    std::vector<Bacterium> filtered;
    for (const auto& b : repo.getBacteria()) {
        if (b.getSpecies() == species)
            filtered.push_back(b);
    }
    return filtered;
}

bool Service::addBacterium(const std::string& name, const std::string& species, int size, const std::vector<std::string>& diseases) {
    for (const auto& b : repo.getBacteria()) {
        if (b.getName() == name && b.getSpecies() == species)
            return false; // duplicate
    }
    repo.addBacterium(Bacterium(name, species, size, diseases));
    return true;
}

void Service::addDisease(const std::string& bacteriumName, const std::string& disease) {
    for (const auto& b : repo.getBacteria()) {
        if (b.getName() == bacteriumName) {
            Bacterium updated = b;
            updated.addDisease(disease);
            repo.updateBacterium(bacteriumName, updated);
            break;
        }
    }
}

void Service::updateBacterium(const std::string& name, const std::string& newSpecies, int newSize) {
    for (const auto& b : repo.getBacteria()) {
        if (b.getName() == name) {
            Bacterium updated = b;
            updated.setSpecies(newSpecies);
            updated.setSize(newSize);
            repo.updateBacterium(name, updated);
            break;
        }
    }
}

void Service::saveAll() {
    repo.saveBacteriaToFile();
}