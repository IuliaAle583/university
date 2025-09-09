#include "Controller.h"
#include "Domain.h"
#include <iostream>
#include <algorithm>

void Controller::addDepartment(HospitalDepartment* d)
{
	this->departments.push_back(d);
}

vector<HospitalDepartment*> Controller::getAllDepartments()
{
	return this->departments;
}

vector<HospitalDepartment*> Controller::getAllEfficitentDepartments()
{
	vector<HospitalDepartment*> result;
	for (auto department : departments) {
		if (department->isEfficient()) {
			result.push_back(department);
		}
	}
	return result;
}

void Controller::writeToFile(string filename)
{
	vector<HospitalDepartment*> sortedDepartments = this->departments;

	sort(sortedDepartments.begin(), sortedDepartments.end(), [](HospitalDepartment* a, HospitalDepartment* b) {
		string typeA = typeid(*a).name();
		string typeB = typeid(*b).name();

		if (typeA == typeB) {
			return a->getName() < b->getName();  
		}
		return typeA < typeB; 
		});
	ofstream fout(filename);
	for (auto department : sortedDepartments) {
		fout << department->toString() << "\n";
	}
	fout.close();
}

void Controller::removeDepartment(const string& name)
{
	auto it = departments.begin();
	while (it != departments.end()) {
		if ((*it)->getName() == name) {
			delete* it;                  
			it = departments.erase(it);  
		}
		else {
			++it; 
		}
	}

}


