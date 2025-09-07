#pragma once
#include <string>
#include <iostream>
#include "service.h"
#include "domain.h"
#include "dynamicVector.h"
#include "repository.h"

class UI {
private:
	Service service;
	Service basketService;	//for the next homework
	int totalCost = 0;
public:
	UI(Service service, Service basketService);
	void initializeCoats();
	void administrator();
	void run();
	void add();
	void remove();
	void update();
	void getCoat();
	static void administratorMenu();
	static void hello();
	static void bye();
	void printAllCoats(int serviceAdminOrUser);
	static void question();
	static void printOneCoat(TrenchCoat printThis);
	void printFilteredCoats(int minSize);

	void printUserMenu();
	static void purchaseMessage();
	static void browser();
	static void addButton();
	void writeToFile();
	void readFromFile();
	void goThroughCoats();
	void addToBasket(TrenchCoat coat);
	//void removeFromBasket(int coatId);
	void printBasket();
	void emptyBasket();
	//print trench?
	void user();

};