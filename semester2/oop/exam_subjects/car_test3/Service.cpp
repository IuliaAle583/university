#include "Service.h"
#include<algorithm>
vector<Car> Service::getAllCars() const
{
	vector<Car> cars = repo.getAllCars();
	sort(cars.begin(), cars.end());
	return cars;
}

vector<Car> Service::getCarsByManufacturer(string manufacturer) const
{
	vector<Car> allCars = repo.getAllCars();
	vector<Car> cars;
	for (const Car& c : allCars)
		if (c.getManufacturer() == manufacturer)
			cars.push_back(c);
	return cars;
}

/// Returns the number of cars that have the given manufacturer.
/// @param manufacturer: the name of the manufacturer to search for.
/// @return: the number of cars with the given manufacturer (>= 0).
int Service::countCarsByManufacturer(const std::string& manufacturer) const
{
	int count = 0;
	for (const auto& car : repo.getAllCars()) {
		if (car.getManufacturer() == manufacturer)
			++count;
	}
	return count;
}
