#include "Service.h"
#include <fstream>
#include <algorithm>


Service::Service()
{
	cars.push_back(new Car(2, new TurboEngine()));
	cars.push_back(new Car(2, new ElectricEngine(400)));
	cars.push_back(new Car(4, new ElectricEngine(100)));
}

Service::~Service()
{
	for (auto* car : cars)
		delete car;
}

void Service::addCar(int nrDoors, string engineType, int autonomy)
{
	if (engineType == "Turbo") {
		cars.push_back(new Car(nrDoors, new TurboEngine()));
	}
	else if (engineType == "Electric") {
		cars.push_back(new Car(nrDoors, new ElectricEngine(autonomy)));
	}
}

vector<Car*> Service::getPriceSmallerThan(double maxPrice)
{
	vector<Car*> res;
	for (auto* car : cars)
		if (car->computePrice() < maxPrice)
			res.push_back(car);
	return res;
}

void Service::writeToFile(const string& fileName, double maxNr)
{
   
    vector<Car*> filteredCars = getPriceSmallerThan(maxNr);

    
    ofstream fout(fileName);
    fout << "Cars with 2 doors:\n";
    for (auto car : filteredCars) {
        if (car->getNrOfDoors() == 2) {
            fout << car->toString() << "\n";
        }
    }
    fout << "Cars with 4 doors:\n";
    for (auto car : filteredCars) {
        if (car->getNrOfDoors() == 4) {
            fout << car->toString() << "\n";
        }
    }
    fout.close();
}

vector<Car*> Service::getAll() const
{
	return this->cars;
}
