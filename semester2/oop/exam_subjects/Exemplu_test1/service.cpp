/*#include "service.h"
#include <algorithm>
#include <iostream>


Service::Service(Repository& repo): repo(repo){}

bool Service::addCar(const Car& car)
{
	int size;
	Car* cars = repo.getAllCars(size);
	for (int i = 0; i < size; i++) {
		if (cars[i].get_model() == car.get_model() && cars[i].get_year() == car.get_year()) {
			return false;
		}
	}
	repo.addCar(car);
	return true;
}

bool Service::removeCar(int year)
{
	int initialSize = 0;
	repo.getAllCars(initialSize);
	repo.removeCar(year);
	int sizeAfter = 0;
	repo.getAllCars(sizeAfter);
	if (initialSize == sizeAfter) {
		return false;
	}
	return true;
}

std::vector<Car> Service::getAllCarsSorted() const
{
	int size;
	Car* cars = repo.getAllCars(size);
	std::vector<Car> sortedCars(cars, cars + size);
	std::sort(sortedCars.begin(), sortedCars.end(), [](const Car& a, const Car& b) {
		if (a.get_name() == b.get_name())
			return a.get_model() < b.get_model();
		return a.get_name() < b.get_name();
		});
	return sortedCars;
}

std::vector<Car> Service::getVintageCarsSorted() const
{
	int size;
	Car* cars = repo.getAllCars(size);
	std::vector<Car> vintageCars;
	for (int i = 0; i < size; i++) {
		if (2024 - cars[i].get_year() > 45) {
			vintageCars.push_back(cars[i]);
		}
	}
	std::sort(vintageCars.begin(), vintageCars.end(), [](const Car& a, const Car& b) {
		return a.get_color() < b.get_color();
		});
	return vintageCars;
}*/

#include "service.h"
#include <iostream>
#include <cstring>  
Service::Service(Repository& repository) : repo(repository) {}

bool Service::addCar(const Car& car) {
    int size;
    Car* cars = repo.getAllCars(size);

    for (int i = 0; i < size; i++) {
        //if (cars[i].get_model() == car.get_model() && cars[i].get_year() == car.get_year()) {
            //std::cout << "Car already exists!\n";
        if (std::strcmp(cars[i].get_model().c_str(), car.get_model().c_str()) == 0 && cars[i].get_year() == car.get_year()) {
            return false;
        }
    }

    repo.addCar(car);
    //std::cout << "Car added successfully!\n";
    return true;
}

bool Service::removeCar(int year) {
    int sizeBefore;
    repo.getAllCars(sizeBefore);

    repo.removeCar(year);

    int sizeAfter;
    repo.getAllCars(sizeAfter);

    if (sizeBefore == sizeAfter) {
        //std::cout << "Car not found!\n";
        return false;
    }

    //std::cout << "Car removed successfully!\n";
    return true;
}

Car* Service::getAllCarsSorted(int& outSize) const {
    int size;
    Car* cars = repo.getAllCars(size);

    Car* sortedCars = new Car[size];  
    for (int i = 0; i < size; i++) {
        sortedCars[i] = cars[i];  
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (sortedCars[i].get_name() > sortedCars[j].get_name() ||
                (sortedCars[i].get_name() == sortedCars[j].get_name() &&
                    sortedCars[i].get_model() > sortedCars[j].get_model()))
            {
                std::swap(sortedCars[i], sortedCars[j]);
            }
        }
    }

    outSize = size;
    return sortedCars;
}

Car* Service::getVintageCarsSorted(int& outSize) const {
    int size;
    Car* cars = repo.getAllCars(size);

    int vintageCount = 0;
    for (int i = 0; i < size; i++) {
        if (2024 - cars[i].get_year() > 45) {
            vintageCount++;
        }
    }

    Car* vintageCars = new Car[vintageCount];
    int index = 0;

    for (int i = 0; i < size; i++) {
        if (2024 - cars[i].get_year() > 45) {
            vintageCars[index++] = cars[i];
        }
    }

    for (int i = 0; i < vintageCount - 1; i++) {
        for (int j = i + 1; j < vintageCount; j++) {
            if (vintageCars[i].get_color() > vintageCars[j].get_color()) {
                std::swap(vintageCars[i], vintageCars[j]);
            }
        }
    }

    outSize = vintageCount;
    return vintageCars;
}

