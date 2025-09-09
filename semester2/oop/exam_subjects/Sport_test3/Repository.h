
#pragma once
#include "Workout.h"
#include <vector>
#include <string>
using namespace std;

class Repository {
private:
    vector<Workout> workouts;

public:
    void loadFromFile(const string& filename);

    vector<Workout> getAll() const;
};