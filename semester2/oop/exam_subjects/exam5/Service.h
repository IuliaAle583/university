//
// Created by mariasiu alexandra on 14.06.2025.
//

#ifndef SERVICE_H
#define SERVICE_H

#include "Repository.h"

class Service {
private:
    Repository& repo;

public:
    Service(Repository& r);

    const std::vector<Biologist>& getAllBiologists() const;
    const std::vector<Bacterium>& getAllBacteria() const;

    std::vector<Bacterium> getBacteriaForSpecies(const std::string& species) const;

    bool addBacterium(const std::string& name, const std::string& species, int size, const std::vector<std::string>& diseases);
    void addDisease(const std::string& bacteriumName, const std::string& disease);

    void updateBacterium(const std::string& name, const std::string& newSpecies, int newSize);
    void saveAll();

};

#endif // SERVICE_H