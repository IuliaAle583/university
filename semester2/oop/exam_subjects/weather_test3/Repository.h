
#pragma once
#include "Domain.h"
#include <string>
#include <vector>
using namespace std;

class Repository {

private:
    vector<weather> elements;
    void LoadData();

public:
    Repository();
    ~Repository();
    vector<weather> getAll();

};
