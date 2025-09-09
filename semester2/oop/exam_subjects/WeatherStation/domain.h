#pragma once
#include <string>
#include "dynamicVector.h"
using namespace std;

class Weather {
private:
	string location;
	string name;
	DynamicVector<std::string> sensors;
public:
	Weather();
	Weather(string loc, string nm, DynamicVector<string>& sensors) : location(loc), name(nm), sensors(sensors) {}

	void setLocation(const string& location);
	void setName(const string& name);
	void setSensors(DynamicVector<std::string> sensors);

	string getLocation() const;
	string getName();
	DynamicVector<string>& getSensors() { return this->sensors; }
};
