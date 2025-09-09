#include "service.h"

Service::Service()
{
	this->repo = Repository();
}

Service::Service(Repository repo)
{
	this->repo = repo;
}

bool Service::add(string& location, string& name, DynamicVector<string> sensors)
{
	for (int i = 0; i < this->repo.getSize(); i++) {
		if (this->repo.getAll()[i].getLocation() == location && this->repo.getAll()[i].getName() == name) {
			return false;
		}
	}
	this->repo.addStation(location, name, sensors);
	return true;
}

DynamicVector<Weather> Service::getAllService()
{
	return this->repo.getAll();
}

DynamicVector<pair<string, int>> Service::countStationsBySensorService(const string& sensor)
{
	return this->repo.countStationsBySensor(sensor);
}
