#pragma once
#include "dynamicVector.h"
#include "domain.h"
class Repository {
private:
	DynamicVector<Patient> patients;
public:
	Repository();
	~Repository();
	void addPatient(const string& name, int age, bool infected, int room);
	DynamicVector<Patient> getAll();
	DynamicVector<Patient> updateInfectionStatus(int age);
	int getSize();
};
