#pragma once

#include "Domain.h"
#include <vector>
#include <string>

class Repository {
private:
    vector<Biologist> biologists;
    vector<Bacterium> bacteria;


public:
    Repository() {
        loadBacteria();
        loadBiolgist();
    }
    void loadBacteria();
    void loadBiolgist();
    const vector<Biologist>& getBiologists() const;
    const vector<Bacterium>& getBacteria() const;

    void addBacteria(const Bacterium& b);
    void updateBacteria(const string& name, const Bacterium& updated);
    ~Repository() {
        saveBacteriaToFile();
    }
    void saveBacteriaToFile();
};
