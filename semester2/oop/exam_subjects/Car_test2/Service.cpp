#include "Service.h"

void Service::generateCars()
{
	this->cars.push_back(Car("Sedan", new ElectricEngine(100)));
	this->cars.push_back(Car("Convertible", new ElectricEngine(10)));
	this->cars.push_back(Car("Sedan", new TurboEngine()));
	this->cars.push_back(Car("Convertible", new TurboEngine()));
}

void Service::addCar(string bodyStyle, string engineType, int autonomy)
{
	Engine* engine;
	if (engineType == "Electric")
		engine = new ElectricEngine(autonomy);
	else
		engine = new TurboEngine();
	this->cars.push_back(Car(bodyStyle, engine));
}

double Service::getPriceOfLastCarAdded()
{
	return this->cars.back().computePrice();
}

vector<Car> Service::getAll()
{
	return this->cars;
}

inline bool Service::functionOfComparison(Car car1, Car car2)
{
	return car1.computePrice() < car2.computePrice();
}

vector<Car> Service::getCarsWithMaxPrice(double maxPrice)
{
	std::vector<Car> carsWithMaximumPrice;
	for (auto car : this->cars)
	{
		if (car.computePrice() < maxPrice)
			carsWithMaximumPrice.push_back(car);
	}
	std::sort(carsWithMaximumPrice.begin(), carsWithMaximumPrice.end(), functionOfComparison);
	return carsWithMaximumPrice;
}

void Service::writeToFile(string fileName, vector<Car> carsToWriteToFile)
{
	std::ofstream writeStream(fileName);
	for (auto car : carsToWriteToFile)
		writeStream << car.toString() << '\n';
	writeStream.close();
}
