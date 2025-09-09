#pragma once
#include "Domain.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Controller
{
private:
	vector<HospitalDepartment*> departments;
public:
	Controller() {
		//initialize with some date
		HospitalDepartment* neonantal1 = new NeonatalUnit("1", 11, 12, 13, 14);
		HospitalDepartment* neonantal2 = new NeonatalUnit("2", 21, 22, 23, 24);

		HospitalDepartment* surgery1 = new Surgery("1", 31, 32);
		HospitalDepartment* surgery2 = new Surgery("2", 41, 42);

		departments.push_back(neonantal1);
		departments.push_back(neonantal2);
		departments.push_back(surgery1);
		departments.push_back(surgery2);
	}
	/*
	* daca folosesc shared ptr asa trb sa fac
	departments.push_back(make_shared<NeonatalUnit>("1", 11, 12, 13, 14));
	departments.push_back(make_shared<NeonatalUnit>("2", 21, 22, 23, 24));
	departments.push_back(make_shared<Surgery>("1", 31, 32));
	departments.push_back(make_shared<Surgery>("2", 41, 42));
	*/
	void addDepartment(HospitalDepartment* d);	// sa nu uit de pointer aici cand adaug
	vector<HospitalDepartment*> getAllDepartments();
	vector<HospitalDepartment*> getAllEfficitentDepartments();
	void writeToFile(string filename);
	~Controller() {
		for (auto department : departments) {
			delete department;
		}
	}

	void removeDepartment(const string& name);
};

