#include "Service.h"
#include<algorithm>
#include<cstring>
#include<fstream>
#include <sstream>

vector<Disorder> Service::getAllDisorders() {
	vector<Disorder> disorders = repository.getDisorders();
	sort(disorders.begin(), disorders.end());
	return disorders;
}

vector<string> Service::getAllSymptomsFromName(string name) {
    vector<Disorder> disorders = repository.getDisorders();
    string allSymptoms = "";

    for (auto& d : disorders) {
        if (d.getName() == name) {
            allSymptoms = d.getList();
            break;
        }
    }
    vector<string> result;
    if (allSymptoms.empty()) return result; 

    stringstream ss(allSymptoms);
    string symptom;

    while (getline(ss, symptom, ',')) {
        
        if (!symptom.empty() && symptom[0] == ' ')
            symptom.erase(0, 1);
        result.push_back(symptom);
    }

    return result;
}
