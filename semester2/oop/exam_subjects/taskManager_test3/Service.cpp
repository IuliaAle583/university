#include "Service.h"
#include <algorithm>

vector<Task> Service::getAllSorted() const {
    vector<Task> result = repo.getAll();
    sort(result.begin(), result.end(), [](const Task& a, const Task& b) {
        if (a.getPriority() == b.getPriority())
            return a.getDuration() < b.getDuration();
        return a.getPriority() < b.getPriority();
        });
    return result;
}

vector<Task> Service::getByPriority(int p) const {
    vector<Task> result;
    for (const Task& t : repo.getAll()) {
        if (t.getPriority() == p)
            result.push_back(t);
    }
    return result;
}

int Service::getTotalDurationByPriority(int p) const {
    int total = 0;
    for (const Task& t : repo.getAll()) {
        if (t.getPriority() == p)
            total += t.getDuration();
    }
    return total;
}