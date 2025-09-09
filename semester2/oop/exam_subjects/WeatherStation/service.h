#pragma once
#include "repository.h"
class Service {
private:
	Repository repo;
public:
	Service();
	Service(Repository repo);
	bool add(string& location, string& name, DynamicVector<string> sensors);
	DynamicVector<Weather> getAllService();
	DynamicVector<pair<string, int>> countStationsBySensorService(const string& sensor);
};
