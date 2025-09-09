//
// Created by mariasiu alexandra on 14.06.2025.
//

#include "Repository.h"
#include <fstream>
#include <sstream>

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> parts;
    std::string token;
    std::istringstream stream(s);
    while (getline(stream, token, delim)) {
        parts.push_back(token);
    }
    return parts;
}

Repository::Repository(const std::string& bioFile, const std::string& bacFile)
    : bioFile(bioFile), bacFile(bacFile)
{
    std::ifstream fin1(bioFile);
    std::string line;
    while (getline(fin1, line)) {
        auto parts = split(line, '|');
        if (parts.size() != 2) continue;
        std::vector<std::string> species = split(parts[1], ',');
        biologists.emplace_back(parts[0], species);
    }
    fin1.close();

    std::ifstream fin2(bacFile);
    while (getline(fin2, line)) {
        auto parts = split(line, '|');
        if (parts.size() != 4) continue;
        std::string name = parts[0];
        std::string species = parts[1];
        int size = std::stoi(parts[2]);
        std::vector<std::string> diseases = split(parts[3], ',');
        bacteria.emplace_back(name, species, size, diseases);
    }
    fin2.close();
}

const std::vector<Biologist>& Repository::getBiologists() const {
    return biologists;
}

const std::vector<Bacterium>& Repository::getBacteria() const {
    return bacteria;
}

void Repository::addBacterium(const Bacterium& b) {
    bacteria.push_back(b);
}

void Repository::updateBacterium(const std::string& name, const Bacterium& updated) {
    for (auto& b : bacteria) {
        if (b.getName() == name) {
            b = updated;
            return;
        }
    }
}

void Repository::saveBacteriaToFile() const {
    std::ofstream fout(bacFile);
    for (const auto& b : bacteria) {
        fout << b.getName() << "|"
            << b.getSpecies() << "|"
            << b.getSize() << "|";
        const auto& d = b.getDiseases();
        for (size_t i = 0; i < d.size(); ++i) {
            fout << d[i];
            if (i < d.size() - 1) fout << ",";
        }
        fout << "\n";
    }
}