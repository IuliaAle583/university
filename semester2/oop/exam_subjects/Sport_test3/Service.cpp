#include "Service.h"
#include <algorithm>

Service::Service(Repository& repo) : repo(repo) {}

vector<Workout> Service::getAllSortedByStartHour() const {
    vector<Workout> all = repo.getAll();
    sort(all.begin(), all.end(), [](const Workout& a, const Workout& b) {
        return a.getStartHour() < b.getStartHour();
        });
    return all;
}

vector<Workout> Service::filterByIntensity(int threshold) const {
    vector<Workout> all = repo.getAll();
    vector<Workout> result;

    for (const auto& w : all)
        if (w.getIntensity() > threshold)
            result.push_back(w);

    return result;
}

vector<Workout> Service::searchByDescriptionAndStartHour(const string& description, int startHour) const {
    vector<Workout> all = repo.getAll();
    vector<Workout> result;

    for (const auto& w : all)
        if (w.getDescription() == description && w.getStartHour() > startHour)
            result.push_back(w);

    return result;
}

int Service::getTotalDurationOf(const vector<Workout>& workouts) const {
    int total = 0;
    for (const auto& w : workouts)
        total += w.getDuration();
    return total;
}