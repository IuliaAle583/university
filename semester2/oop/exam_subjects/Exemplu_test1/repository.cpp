#include "repository.h"

void Repository::resize()
{
	int newCapacity = 2 * capacity;
	Car* newCars = new Car[newCapacity];

	for (int i = 0; i < size; i++) {
		newCars[i] = cars[i];
	}

	delete[] cars;
	cars = newCars;
	capacity = newCapacity;
}

Repository::Repository(int capacity)
{
	this->capacity = capacity;
	this->size = 0;
	this->cars = new Car[capacity];
}

Repository::~Repository()
{
	delete[] cars;
}

void Repository::addCar(const Car& car)
{
	if (size == capacity) {
		resize();
	}
	cars[size++] = car;
}

void Repository::removeCar(int year)
{
	for (int i = 0; i < size; i++) {
		if (cars[i].get_year() == year) {
			for (int j = i; j < size - 1; j++) {
				cars[j] = cars[j + 1];
			}
			size--;
		}
	}
}

Car* Repository::getAllCars(int& outSize) const
{
	outSize = size;
	return cars;
}
