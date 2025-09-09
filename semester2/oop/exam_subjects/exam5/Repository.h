//
// Created by mariasiu alexandra on 14.06.2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Domain.h"
#include <vector>
#include <string>

class Repository {
private:
    std::vector<Biologist> biologists;
    std::vector<Bacterium> bacteria;
    std::string bioFile, bacFile;

public:
    Repository(const std::string& bioFile, const std::string& bacFile);

    const std::vector<Biologist>& getBiologists() const;
    const std::vector<Bacterium>& getBacteria() const;

    void addBacterium(const Bacterium& b);
    void updateBacterium(const std::string& name, const Bacterium& updated);
    void saveBacteriaToFile() const;
};

#endif // REPOSITORY_H