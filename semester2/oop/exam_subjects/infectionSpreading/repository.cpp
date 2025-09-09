#include "repository.h"

Repository::Repository()
{
	this->patients = DynamicVector<Patient>();
}

Repository::~Repository()
{
	this->patients.clear();
}

void Repository::addPatient(const string& name, int age, bool infected, int room)
{
	Patient patient = Patient(name, age, infected, room);
	this->patients.append(patient);
}

DynamicVector<Patient> Repository::getAll()
{
	return this->patients;
}

DynamicVector<Patient> Repository::updateInfectionStatus(int age)
{
    DynamicVector<Patient> result;
    std::vector<int> toUpdate; 

    for (int i = 0; i < getSize(); i++) {
        if (patients[i].getAge() > age && !patients[i].getInfected()) {
            for (int j = 0; j < getSize(); j++) {
                if (patients[j].getRoomNumber() == patients[i].getRoomNumber() && patients[j].getInfected()) {
                    toUpdate.push_back(i); 
                    break;
                }
            }
        }
    }

    for (int idx : toUpdate) {
        Patient& patient = patients[idx];  
        patient.setInfected(true);
        result.append(patients[idx]); 
    }

    return result;
}


int Repository::getSize()
{
	return this->patients.getSize();
}
