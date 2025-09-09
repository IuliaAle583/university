
#include "Repository.h"
#include <fstream>
#include <stdexcept>

void Repository::loadFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    workouts.clear();
    string line;
    while (getline(fin, line)) {
        size_t p1 = line.find(';');
        size_t p2 = line.find(';', p1 + 1);
        size_t p3 = line.find(';', p2 + 1);
        size_t p4 = line.find(';', p3 + 1);

        int startHour = stoi(line.substr(0, p1));
        int endHour = stoi(line.substr(p1 + 1, p2 - p1 - 1));
        string type = line.substr(p2 + 1, p3 - p2 - 1);
        int intensity = stoi(line.substr(p3 + 1, p4 - p3 - 1));
        string description = line.substr(p4 + 1);

        workouts.push_back(Workout(startHour, endHour, type, intensity, description));
    }

    fin.close();
}

vector<Workout> Repository::getAll() const {
    return workouts;
}