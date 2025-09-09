/*#pragma once
#include "repository.h"
#include <vector>

class Service {
private:
	Repository& repo;
public:
	Service(Repository& repo);
	bool addCar(const Car& car);
	bool removeCar(int year);
	std::vector<Car> getAllCarsSorted() const;
	std::vector<Car> getVintageCarsSorted() const;
};*/

#pragma once
#include "repository.h"

class Service {
private:
    Repository& repo;

public:
    Service(Repository& repository);

    bool addCar(const Car& car);
    bool removeCar(int year);
    Car* getAllCarsSorted(int& outSize) const;
    Car* getVintageCarsSorted(int& outSize) const;
};

