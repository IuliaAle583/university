#include <cassert>
#include <string>
#include "service.h"


void testAdd() {
	Repository repo;
	Service service;
	//UI ui(service);
	string name1 = "John";
	bool result = service.add(name1, 30, false, 101);

	assert(result == true);  
	DynamicVector<Patient> allPatients = service.getAllService();
	assert(allPatients.getSize() == 1);  

	string name2 = "John";  
	result = service.add(name2, 25, true, 102);

	assert(result == false);  
	allPatients = service.getAllService();
	assert(allPatients.getSize() == 1);
}

void testUpdate() {
	Repository repo;
	Service service;
	string name = "Anna";
	service.add(name, 23, false, 102);
	name = "Ana";
	service.add(name, 30, true, 102);
	DynamicVector<Patient> updated = service.updateService(20);
	//assert(repo.getSize() == 2);
	//assert(updated[1].getInfected() == true);
	assert(updated[0].getInfected() == true);
}
void callAllTests() {
	testAdd();
	testUpdate();
}