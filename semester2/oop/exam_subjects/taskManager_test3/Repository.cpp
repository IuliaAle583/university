#include "Repository.h"
#include <fstream>

string trim(const string& s) {
    int start = 0;
    while (start < s.size() && isspace(s[start])) start++;
    int end = s.size() - 1;
    while (end >= 0 && isspace(s[end])) end--;
    return s.substr(start, end - start + 1);
}

void Repository::loadFromFile(const string& filename) {
    ifstream fin(filename);
    string line;

    while (getline(fin, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        string desc = trim(line.substr(0, pos1));
        int dur = stoi(trim(line.substr(pos1 + 1, pos2 - pos1 - 1)));
        int pri = stoi(trim(line.substr(pos2 + 1)));

        tasks.push_back(Task(desc, dur, pri));
    }

    fin.close();
}

const vector<Task>& Repository::getAll() const {
    return tasks;
}