#pragma once
#include "Repository.h"
class Service {
private:
    Repository& repo;

public:
    Service(Repository& repo):repo(repo){}
    bool addBacteria(const string& name, const string& species, int size, const vector<string>& diseases);
    void addDisease(const string& bacteriumName, const string& disease);

    void updateBacteria(const string& name, const string& newSp, int newSi);
    vector<Bacterium> getBacteriaForSpecies(const string& species) const;
    const vector<Biologist>& getAllBiologists() const {
        return repo.getBiologists();
    }
    const std::vector<Bacterium>& getAllBacteria() const {
        return repo.getBacteria();
    }
   

};

