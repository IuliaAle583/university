#include "repository.h"

void Repository::addStation(string& location, string& name, DynamicVector<string>& sensors)
{
	Weather weather = Weather(location, name, sensors);
	this->weathers.append(weather);
}

DynamicVector<Weather> Repository::getAll()
{
	return this->weathers;
}

DynamicVector<pair<string, int>> Repository::countStationsBySensor(const string& sensor)
{
	DynamicVector<pair<string, int>> sensorCount;
	for (int i = 0; i < weathers.getSize(); i++) {
		Weather& station = weathers[i];
		DynamicVector<string>& sensors = station.getSensors();
	
		bool hasSensors = false;
		for (int j = 0; j < sensors.getSize(); j++) {
			if (sensors[j] == sensor) {
				hasSensors = true;
				break;
			}
		}
		if (hasSensors) {
			bool found = false;
			for (int k = 0; k < sensorCount.getSize(); k++) {
				if (sensorCount[k].first == station.getLocation()) {
					sensorCount[k].second++;  
					found = true;
					break;
				}
			}

			if (!found) {
				sensorCount.append(make_pair(station.getLocation(), 1));
			}
		}
	}
	return sensorCount;
}

int Repository::getSize()
{
	return weathers.getSize();
}
