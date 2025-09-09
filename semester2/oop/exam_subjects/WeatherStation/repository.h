#pragma once
#include "domain.h"
#include "dynamicVector.h"

class Repository {
private:
	DynamicVector<Weather> weathers;
public:
	void addStation(string& location, string& name, DynamicVector<string>& sensors);
	DynamicVector<Weather> getAll();
	DynamicVector<pair<string, int>> countStationsBySensor(const string& sensor);
	int getSize();
};
