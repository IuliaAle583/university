#include "Repository.h"
#include <fstream>
#include <sstream>
using namespace std;

static vector<string> split(const string& str, char delimitator) {
    vector<string> parts;
    string token;
    istringstream iss(str);
    while (getline(iss, token, delimitator)) {
        parts.push_back(token);
    }
    return parts;
}

const vector<Biologist>& Repository::getBiologists() const
{
    return this->biologists;
}

const vector<Bacterium>& Repository::getBacteria() const
{
    return this->bacteria;
}

void Repository::addBacteria(const Bacterium& b)
{
    bacteria.push_back(b);
}

void Repository::loadBacteria()
{
    ifstream fin(R"(D:\desktop2\oop\exam\bacteria.txt)");
    string line;
    while (getline(fin, line)) {
        auto parts = split(line, '|');
        if (parts.size() != 4) continue;
        string name = parts[0];
        string species = parts[1];
        int size = stoi(parts[2]);
        vector<string> diseases = split(parts[3], ',');
        bacteria.emplace_back(name, species, size, diseases);
    }
    fin.close();
}

void Repository::loadBiolgist()
{
    ifstream fin(R"(D:\desktop2\oop\exam\biologists.txt)");
    string line;
    while (getline(fin, line)) {
        auto parts = split(line, '|');
        if (parts.size() != 2) continue;
        vector<string> species = split(parts[1], ',');
        biologists.emplace_back(parts[0], species);
    }
    fin.close();
}


void Repository::updateBacteria(const string& name, const Bacterium& updated)
{
    for (auto& bact : bacteria) {
        if (bact.getName() == name) {
            bact = updated;
            return;
        }
    }
}

void Repository::saveBacteriaToFile()
{
    ofstream fout(R"(D:\desktop2\oop\exam\bacteria.txt)");
    for (const auto bact : bacteria) {
        fout << bact.getName() << "|" << bact.getSpecies() << "|" << bact.getSize() << "|";
        const auto& disease = bact.getDiseases();
        for (size_t i = 0; i < disease.size(); ++i) {
            fout << disease[i];
            if (i < disease.size() - 1) fout << ",";
        }
        fout << "\n";
    }
}
