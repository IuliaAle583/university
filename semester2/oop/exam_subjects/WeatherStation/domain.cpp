#include "domain.h"

Weather::Weather(): location("0"), name("0"), sensors()
{
}

void Weather::setLocation(const string& location)
{
	this->location = location;
}

void Weather::setName(const string& name)
{
	this->name = name;
}

void Weather::setSensors(DynamicVector<std::string> sensors)
{
	this->sensors = sensors;
}

string Weather::getLocation() const
{
	return this->location;
}

string Weather::getName()
{
	return this->name;
}


