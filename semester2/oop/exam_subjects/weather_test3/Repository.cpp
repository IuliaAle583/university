
#include "Repository.h"
#include <fstream>

void Repository::LoadData() {
    ifstream inFile(R"(D:\desktop2\teste_oop\weather3\1.txt)");
    weather CurrentElement;
    this->elements.clear();
    while (inFile >> CurrentElement)
    {
        this->elements.push_back(CurrentElement);
    }
    inFile.close();
}

Repository::Repository() {
    this->LoadData();
}

Repository::~Repository() {

}

vector<weather> Repository::getAll() {
    return this->elements;
}