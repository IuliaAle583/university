#include "service.h"

bool Service::add(string& name, int age, bool infected, int room)
{
	DynamicVector<Patient> patients = repo.getAll();
	for (int i = 0; i < patients.getSize(); i++) {
		if (patients[i].getName() == name) {
			return false;
		}
	}
	repo.addPatient(name, age, infected, room);
	return true;
}

DynamicVector<Patient> Service::updateService(int age)
{
	return repo.updateInfectionStatus(age);
}

DynamicVector<Patient> Service::getAllService()
{
	return repo.getAll();
}
