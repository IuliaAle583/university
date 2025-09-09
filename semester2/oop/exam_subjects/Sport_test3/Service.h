#pragma once
#include "Repository.h"
#include <vector>
#include <string>
using namespace std;

class Service {
private:
    Repository& repo;

public:
    Service(Repository& repo);

    vector<Workout> getAllSortedByStartHour() const;
    vector<Workout> filterByIntensity(int threshold) const;
    vector<Workout> searchByDescriptionAndStartHour(const string& description, int startHour) const;
    int getTotalDurationOf(const vector<Workout>& workouts) const;
};