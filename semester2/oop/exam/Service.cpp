#include "Service.h"


vector<Bacterium> Service::getBacteriaForSpecies(const string& species) const
{
    vector<Bacterium> fBacteria;
    for (const auto& bact : repo.getBacteria()) {
        if (bact.getSpecies() == species)
            fBacteria.push_back(bact);
    }
    return fBacteria;
}

bool Service::addBacteria(const string& name, const string& species, int size, const vector<string>& diseases)
{
    for (const auto& bact : repo.getBacteria()) {
        if (bact.getName() == name && bact.getSpecies() == species)
            return false; 
    }
    repo.addBacteria(Bacterium(name, species, size, diseases));
    return true;
}

void Service::updateBacteria(const string& name, const string& newSp, int newSi)
{
    for (const auto& bact : repo.getBacteria()) {
        if (bact.getName() == name) {
            Bacterium newBact = bact;
            newBact.setSpecies(newSp);
            newBact.setSize(newSi);
            repo.updateBacteria(name, newBact);
            break;
        }
    }
}

void Service::addDisease(const string& name, const string& disease)
{
    for (const auto& bact : repo.getBacteria()) {
        if (bact.getName() == name) {
            Bacterium newB = bact;
            newB.addDisease(disease);
            repo.updateBacteria(name, newB);
            break;
        }
    }
}


