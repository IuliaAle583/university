#pragma once
#include "repository.h"
class Service {
private:
	Repository repo;
public:
	bool add(string& name, int age, bool infected, int room);
	DynamicVector<Patient> updateService(int age);
	DynamicVector<Patient> getAllService();
};
