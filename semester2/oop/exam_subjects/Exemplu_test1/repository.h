#pragma once
#include "domain.h"

class Repository {
private:
	Car* cars;
	int size;
	int capacity;

	void resize();

public:
	Repository(int capacity = 10);
	~Repository();
	void addCar(const Car& car);
	void removeCar(int year);
	Car* getAllCars(int& outSize) const;
};
