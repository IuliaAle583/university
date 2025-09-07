#include "ui.h"
#include <string>
#include <iostream>
#include <utility>
#include <cstdlib>

using namespace std;
#define MAX_LEN 50

void UI::printFilteredCoats(int minSize) {
	DynamicVector<TrenchCoat> filteredCoats = this->service.filterBySize(minSize);
	for (int i = 0; i < filteredCoats.getSize(); i++) {
		printOneCoat(filteredCoats[i]);
	}
}

void UI::printUserMenu()
{
	std::cout << std::endl;
	std::cout << "***********USER*MODE***********" << std::endl;
	std::cout << "1. Browse through all trench coats" << std::endl;
	std::cout << "2. Display all trench coats in the shopping cart" << std::endl;
	std::cout << "3. Purchase all trench coats in the shopping cart" << std::endl;
	std::cout << "4. Exit" << std::endl;
	std::cout << "> ";
}

void UI::purchaseMessage()
{
	std::cout << "Thank you for shopping!" << std::endl;
}

void UI::browser()
{
	std::cout << std::endl;
	std::cout << "Enter 1 to go the previous trench coat, ";
	std::cout << "2 to go to the next trench coat, ";
	std::cout << "3 to add the trench coat to the shopping basket, ";
	std::cout << "and 4 to exit the cycle." << std::endl;
	std::cout << endl;
}

void UI::addButton()
{
	std::cout << "***********************" << std::endl;
	std::cout << "******ADD*TO*CART******" << std::endl;
	std::cout << "***********************" << std::endl;
	std::cout << std::endl;
}

void UI::writeToFile()
{
	this->service.saveProgress();
}

void UI::readFromFile()
{
	this->service.loadFile();
	std::cout << "the database has been loaded!" << std::endl;
}



void UI::goThroughCoats()
{
	std::cout << "Total cost so far: " << this->totalCost << std::endl;
	int size;
	std::cout << "Enter the size of the trench coats you want to see,";
	std::cout << " or press 0 to see all trench coats> " << std::endl;
	std::cin >> size;
	int index = 0;
	int command;
	this->browser();
	DynamicVector<TrenchCoat> coats;
	if (size != 0) {
		coats = this->service.filterBySize(size);
	}
	else {
		coats = this->service.getAll();
	}
	std::cin >> command;
	if (coats.getSize() == 0) {
		std::cout << "There are no trench coats with that size!" << std::endl;
		return;
	}
	else {
		while (command != 4) {
			if (command == 1) {
				if (index == 0) {
					index = coats.getSize() - 1; {
						this->printOneCoat(coats[index]);
						std::string completeUrl = "https://www.google.com/search?q=" + coats[index].getPhotoLink();
						system(std::string("start " + completeUrl).c_str());
						
						this->addButton();
					}
				}
				else {
					index--; {
						this->printOneCoat(coats[index]);
						this->addButton();
					}
				}
			}
			else if (command == 2) {
				if (index == coats.getSize() - 1) {
					index = 0; {
						this->printOneCoat(coats[index]);
						this->addButton();
					}
				}
				else {
					index++; {
						this->printOneCoat(coats[index]);
						this->addButton();
					}
				}
			}
			else if (command == 3) {
				this->addToBasket(coats[index]);
				std::cout << "Added trench coat to basket." << std::endl;
				totalCost += coats[index].getPrice();
				std::cout << "Total cost is: " << totalCost << std::endl;
			}
			else {
				std::cout << "Invalid command!" << std::endl;
			}
			std::cout << ">";
			std::cin >> command;
		}
	}

}

void UI::addToBasket(TrenchCoat coat)
{
	this->basketService.addCoat(coat.getId(), coat.getSize(), coat.getColour(), coat.getPrice(), coat.getQuantity(), coat.getPhotoLink());
}



void UI::printBasket()
{
	//int totalCost = 0;
	DynamicVector<TrenchCoat> basket = this->basketService.getAll();
	for (int i = 0; i < basket.getSize(); i++) {
		this->printOneCoat(basket[i]);
		//this->totalCost += basket[i].getPrice();
	}
	std::cout << "Cost: " << this->totalCost << std::endl;
}

void UI::emptyBasket()
{
	DynamicVector<TrenchCoat> basket = this->basketService.getAll();
	for (int i = 0; i < basket.getSize(); i++) {
		this->service.updateCoat(basket[i].getId(), basket[i].getId(), basket[i].getSize(), basket[i].getColour(), basket[i].getPrice(), basket[i].getQuantity()-1, basket[i].getPhotoLink());
		this->basketService.removeCoat(basket[i].getId());

	}
	this->totalCost = 0;
}

void UI::user()
{
	this->printUserMenu();
	this->service.loadFile();
	int command;
	std::cin >> command;
	while (command < 4 && command>0) {
		switch (command) {
		case 1:
			this->goThroughCoats();
			break;
		case 2:
			this->printBasket();
			break;
		case 3:
			this->purchaseMessage();
			this->emptyBasket();
			break;
		case 4:
			this->bye();
			break;
		default:
			std::cout << "Invalid command!" << std::endl;
			break;
		}
		this->printUserMenu();
		std::cin >> command;
	}
}

UI::UI(Service service, Service basketService) {
	this->service = std::move(service);
	this->basketService = std::move(basketService);
	//this->initializeCoats();
}

void UI::initializeCoats() {
	this->service.addCoat(1, 38, "Red", 100, 10, "http://example.com/photo1");
	this->service.addCoat(2, 40, "Blue", 120, 5, "http://example.com/photo2");
	this->service.addCoat(3, 42, "Green", 150, 8, "http://example.com/photo3");
	this->service.addCoat(4, 44, "Black", 180, 12, "http://example.com/photo4");
	this->service.addCoat(5, 46, "White", 130, 6, "http://example.com/photo5");
	this->service.addCoat(6, 48, "Yellow", 110, 7, "http://example.com/photo6");
	this->service.addCoat(7, 50, "Purple", 160, 9, "http://example.com/photo7");
	this->service.addCoat(8, 30, "Pink", 90, 15, "http://example.com/photo8");
	this->service.addCoat(9, 32, "Orange", 140, 11, "http://example.com/photo9");
	this->service.addCoat(10, 34, "Gray", 200, 4, "http://example.com/photo10");
}

void UI::hello() {
	std::cout << "Welcome to ProperTrenchCoat, Administrator. What do you want to do?" << std::endl;
}

void UI::question() {
	std::cout << "***WELCOME TO PROPER TRENCH COATS***" << std::endl;
	std::cout << "Do you want to be an Administrator or an User?" << std::endl;
	std::cout << "Enter 1 for administrator, 2 for user and 0 to exit..." << std::endl;
}

void UI::printOneCoat(TrenchCoat printThis) {
	std::cout << "ID: " << printThis.getId() << std::endl;
	std::cout << "Size: " << printThis.getSize() << std::endl;
	std::cout << "Colour: " << printThis.getColour() << std::endl;
	std::cout << "Price: " << printThis.getPrice() << std::endl;
	std::cout << "Quantity: " << printThis.getQuantity() << std::endl;
	std::cout << "Photograph: " << printThis.getPhotoLink() << std::endl;
	std::cout << std::endl;
}

void UI::administratorMenu() {
	std::cout << std::endl;
	std::cout << "**************ADMINISTRATOR MODE**************" << std::endl;
	std::cout << "1. Add a trench coat" << std::endl;
	std::cout << "2. Remove a trench coat" << std::endl;
	std::cout << "3. Update a trench coat" << std::endl;
	//std::cout << "4. Get a trench coat" << std::endl;
	std::cout << "4. Print all trench coats" << std::endl;
	std::cout << "5. Filter trench coats by size" << std::endl;
	std::cout << "6. Read from database" << std::endl;
	std::cout << "7. Write to database" << std::endl;
	std::cout << "8. Exit" << std::endl;
	std::cout << "> ";
}

void UI::bye()
{
	std::cout << "Goodbye!" << std::endl;
}


void UI::printAllCoats(int serviceAdminOrUser) {
	if (serviceAdminOrUser == 1) {
		DynamicVector<TrenchCoat>allCoats = this->service.getAll();
		for (int i = 0;i < allCoats.getSize(); i++) {
			{
				printOneCoat(allCoats[i]);
			}
		}
	}
	else {
		DynamicVector<TrenchCoat> allCoats = this->basketService.getAll();
		for (int i = 0; i < allCoats.getSize(); i++) {
			TrenchCoat trench = allCoats[i];
			std::cout << "ID: " << trench.getId() << " || "
				<< "Size: " << trench.getSize() << " || "
				<< "Colour: " << trench.getColour() << " || "
				<< "Price: " << trench.getPrice() << " || "
				<< "Quantity: " << trench.getQuantity() << " || "
				<< "Link: " << trench.getPhotoLink()
				<< std::endl;
		}
	}
}

void UI::administrator() {
	this->hello();
	this->administratorMenu();
	int command;
	std::cin >> command;
	while (command < 8 && command>0) {
		switch (command) {
		case 1:
			this->add();
			break;
		case 2:
			this->remove();
			break;
		case 3:
			this->update();
			break;
		//case 4:
			//this->getCoat();
			//break;
		case 4:
			this->printAllCoats(1);
			break;

		case 5:
			int minSize;
			std::cout << "Enter minimum size: ";
			std::cin >> minSize;
			this->printFilteredCoats(minSize);
			break;

		case 6:
			this->readFromFile();
			break;

		case 7:
			this->writeToFile();
			std::cout << "writing to database..." << std::endl;
			break;

		case 8:
			bye();
			break;

		default:
			std::cout << "invalid command" << std::endl;
			break;
		}
		std::cout << endl;
		this->administratorMenu();
		std::cin >> command;
	}
	this->bye();
}


void UI::run() {
	this->question();
	int command;
	std::cin >> command;
	while (command < 3 && command > 0)
	{
		switch (command)
		{
		case 1:
			this->administrator();
			break;
		case 2:
			this->user();
			break;
		default:
			std::cout << "Invalid command!" << std::endl;
			break;
		}
		this->question();
		std::cin >> command;
	}
	this->bye();
}

void UI::remove() {
	int trenchID;
	std::cout << "Enter the ID of the trench coat you want to remove: ";
	std::cin >> trenchID;

	while (trenchID <= 0) {
		std::cout << "The ID must be a positive integer!" << std::endl;
		std::cout << "Enter the ID of the trench coat you want to remove: ";
		std::cin >> trenchID;
	}

	if (!this->service.checkIfExists(trenchID)) {
		std::cout << ("The trench coat does not exist!") << std::endl;
	}
	else {
		std::cout << "Removing trench coat..." << std::endl;
		this->service.removeCoat(trenchID);
		std::cout << "Trench coat removed!" << std::endl;
	}
}

void UI::add() {
	int trenchID, trenchSize, trenchQuantity,trenchPrice;
	char trenchColour[MAX_LEN], photoLink[MAX_LEN];

	std::cout << "enter ID: ";
	std::cin >> trenchID;

	while (trenchID <= 0) {
		std::cout << "The ID must be a positive integer!" << std::endl;
		std::cout << "Enter the ID of the trench coat: ";
		std::cin >> trenchID;
	}

	std::cout << "Enter the size of the trench coat: ";
	std::cin >> trenchSize;

	while (trenchSize < 30 || trenchSize > 50) {
		std::cout << "The size must be in the range [30,50]!" << std::endl;
		std::cout << "Enter the size of the trench coat: ";
		std::cin >> trenchSize;
	}

	std::cout << "Enter the colour of the trench coat: ";
	std::cin.ignore();
	std::cin >> trenchColour;

	std::cout << "Enter the price of the trench coat: ";
	std::cin.ignore();
	std::cin >> trenchPrice;

	while (trenchPrice <= 0) {
		std::cout << "The price must be a positive number!" << std::endl;
		std::cout << "Enter the price of the trench coat: ";
		std::cin.ignore();
		std::cin >> trenchPrice;
	}

	std::cout << "Enter the quantity of the trench coat: ";
	std::cin.ignore();
	std::cin >> trenchQuantity;

	while (trenchQuantity <= 0) {
		std::cout << "The quantity must be a positive integer!" << std::endl;
		std::cout << "Enter the quantity of the trench coat: ";
		std::cin.ignore();
		std::cin >> trenchQuantity;
	}

	std::cout << "Enter the photography link of the trench coat: ";
	std::cin.ignore();
	std::cin >> photoLink;

	std::cout << "Adding trench coat..." << std::endl;

	if (this->service.addCoat(trenchID,trenchSize,trenchColour,trenchPrice,trenchQuantity,photoLink)) {
		std::cout << "Trench coat added!" << std::endl;
	}
	else {
		std::cout << "Trench coat with this ID already exists!" << std::endl;
	}

}

void UI::update() {
	int trenchOldID, trenchID, trenchSize, trenchQuantity,trenchPrice;
	std::string trenchColour, photoLink;

	std::cout << "Enter the ID of the trench coat: ";
	std::cin >> trenchOldID;

	if (!this->service.checkIfExists(trenchOldID)) {
		std::cout << ("The trench coat does not exist!") << std::endl;
	}
	else {
		std::cout << "Enter the new ID of the trench coat: ";
		std::cin >> trenchID;

		if (this->service.checkIfExists(trenchOldID) > 1) {
			std::cout << ("There already is a trench coat with that ID!") << std::endl;
		}
		else {
			while (trenchOldID <= 0) {
				std::cout << "The ID must be a positive integer!" << std::endl;
				std::cout << "Enter the ID of the trench coat: ";
				std::cin >> trenchID;
			}

			std::cout << "Enter the size of the trench coat: ";
			std::cin >> trenchSize;

			while (trenchSize <= 30 || trenchSize >= 50) {
				std::cout << "The size must be in the range [30,50]!" << std::endl;
				std::cout << "Enter the size of the trench coat: ";
				std::cin >> trenchSize;
			}

			std::cout << "Enter the colour of the trench coat: ";
			std::cin >> trenchColour;

			std::cout << "Enter the price of the trench coat: ";
			std::cin >> trenchPrice;

			while (trenchPrice <= 0) {
				std::cout << "The price must be a positive number!" << std::endl;
				std::cout << "Enter the price of the trench coat: ";
				std::cin >> trenchPrice;
			}

			std::cout << "Enter the quantity of the trench coat: ";
			std::cin >> trenchQuantity;

			while (trenchQuantity <= 0) {
				std::cout << "The quantity must be a positive integer!" << std::endl;
				std::cout << "Enter the quantity of the trench coat: ";
				std::cin >> trenchQuantity;
			}

			std::cout << "Enter the photography link of the trench coat: ";
			std::cin >> photoLink;

			std::cout << "Updating trench coat..." << std::endl;
			this->service.updateCoat(trenchOldID, trenchID, trenchSize,trenchColour,trenchPrice,trenchQuantity,photoLink);
		}
	}
}

void UI::getCoat()
{
	int id;
	std::cout << "Enter the ID of the trench coat you want to get: ";
	std::cin >> id;

	while (id <= 0) {
		std::cout << "The ID must be a positive integer!" << std::endl;
		std::cout << "Enter the ID of the trench coat you want to get: ";
		std::cin >> id;
	}

	if (!this->service.checkIfExists(id)) {
		std::cout << ("The trench coat does not exist!") << std::endl;
	}
	else {
		std::cout << "Getting trench coat..." << std::endl;
		this->service.getCoat(id);
		std::cout << "The Trench Coat! Is here!" << std::endl;
	}
}
