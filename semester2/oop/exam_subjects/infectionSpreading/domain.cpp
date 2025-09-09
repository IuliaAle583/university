#include "domain.h"

Patient::Patient()
{
	this->age = 0;
	this->infected = false;
	this->name = "0";
	this->roomNumber = 0;
}

Patient::Patient(string name, int age, bool infected, int roomNumber)
{
	this->age = age;
	this->infected = infected;
	this->name = name;
	this->roomNumber = roomNumber;
}

void Patient::setName(const string& name)
{
	this->name = name;
}

void Patient::setAge(int age)
{
	this->age = age;
}

void Patient::setInfected(bool infected)
{
	this->infected = infected;
}

void Patient::setRoom(int number)
{
	this->roomNumber = number;
}

string Patient::getName()
{
	return this->name;
}

int Patient::getAge()
{
	return this->age;
}

bool Patient::getInfected()
{
	return this->infected;
}

int Patient::getRoomNumber()
{
	return this->roomNumber;
}


