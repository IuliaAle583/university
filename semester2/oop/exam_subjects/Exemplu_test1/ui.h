#pragma once
#include "service.h"

class UI {
private:
	Service& service;

	void menu();
	void addCar();
	void removeCar();
	void showAllCars();
	void showVintageCars();
public:
	UI(Service& service);
	void run();
};
