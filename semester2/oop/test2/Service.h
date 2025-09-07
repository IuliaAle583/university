#pragma once
#include "Car.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Service {
private:
	vector<Car*> cars;
public:
	Service();
	~Service();
	void addCar(int nrDoors, string engineType, int autonomy);
	vector<Car*> getPriceSmallerThan(double maxPrice);
	void writeToFile(const string& fileName, double maxPrice);
	vector<Car*> getAll() const;
};

