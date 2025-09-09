#include "service.h"
#include <cassert>
void testAdd() {
	Repository repo;
	Service service(repo);
	DynamicVector<Weather> result = service.getAllService();
	string name = "ana", location = "new york";
	DynamicVector<string> sensors1;
	sensors1.append("Temperature");
	sensors1.append("Humidity");


	service.add(name, location, sensors1);
	assert(result.getSize() == 3);

	DynamicVector<string> sensors2;
	sensors2.append("Pressure");
	sensors2.append("Humidity");
	location = "new york";
	name = "jfk airport";
	service.add(location, name, sensors2);
	assert(result.getSize() == 3);

}

void testCountStationsBySensor()
{
    Repository repo;

    DynamicVector<string> sensors1;
    sensors1.append("Temperature");
    sensors1.append("Humidity");

    DynamicVector<string> sensors2;
    sensors2.append("Pressure");
    sensors2.append("Humidity");

    DynamicVector<string> sensors3;
    sensors3.append("Temperature");
    sensors3.append("Pressure");

    string name, location;
    name = "central park";
    location = "new york";
    repo.addStation(location, name, sensors1);
    name = "kjabsd";
    location = "new york";
    repo.addStation(location, name, sensors2);
    name = "sdf";
    location = "new york";
    repo.addStation(location, name, sensors3);
    name = "ajshbd";
    location = "new york";
    repo.addStation(location, name, sensors1);

    string sensor = "Temperature";
    DynamicVector<pair<string, int>> result = repo.countStationsBySensor(sensor);

    //assert(akjsbfhasvfyuew)
}

void call() {
	testAdd();
    testCountStationsBySensor();
}