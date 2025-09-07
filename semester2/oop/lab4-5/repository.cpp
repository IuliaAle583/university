#include <iostream>
#include <string>
#include "repository.h"

void Repository::addCoat(int trenchID, int trenchSize, const std::string& trenchColour, int trenchPrice, int trenchQuantity, const std::string& photoLink) {
	// Adds a new trench coat to the repository
	// @param trenchID: The ID of the trench coat
	// @param trenchSize: The size of the trench coat
	// @param trenchColour: The color of the trench coat
	// @param trenchPrice: The price of the trench coat
	// @param trenchQuantity: The quantity of the trench coat
	// @param photoLink: The link to the photo of the trench coat
	TrenchCoat trench = TrenchCoat(trenchID, trenchSize, trenchColour, trenchPrice, trenchQuantity, photoLink);
	this->coats.append(trench);
}

void Repository::removeCoat(int trenchID) {
	// Removes a trench coat from the repository by its ID
	// @param trenchID: The ID of the trench coat to remove
	for (int i = 0; i < this->coats.getSize(); i++) {
		if (this->coats[i].getId() == trenchID) {
			this->coats.remove(i);
			return;
		}
	}
}

void Repository::updateCoat(int trenchOldID, int trenchID, int trenchSize, const std::string& trenchColour, int trenchPrice, int trenchQuantity, const std::string& photoLink) {
	// Updates an existing trench coat's information
	// @param trenchOldID: The old ID of the trench coat to be updated
	// @param trenchID: The new ID of the trench coat
	// @param trenchSize: The new size of the trench coat
	// @param trenchColour: The new color of the trench coat
	// @param trenchPrice: The new price of the trench coat
	// @param trenchQuantity: The new quantity of the trench coat
	// @param photoLink: The new photo link of the trench coat
	this->removeCoat(trenchOldID);
	this->addCoat(trenchID,trenchSize, trenchColour, trenchPrice, trenchQuantity, photoLink);

}

bool Repository::validID(int trenchID) {
	// Checks if a trench coat ID exists in the repository
	// @param trenchID: The ID to check
	// @return: True if the trench coat ID exists, otherwise false
	for (int i = 0; i < this->coats.getSize(); i++) {
		if (this->coats[i].getId() == trenchID) {
			return true;
		}
	}
	return false;
}

TrenchCoat Repository::getCoat(int trenchID) {
	// Retrieves a trench coat from the repository by its ID
	// @param trenchID: The ID of the trench coat to retrieve
	// @return: The trench coat with the specified ID, or a default trench coat if not found
	for (int i = 0; i < this->coats.getSize(); i++) {
		if (this->coats[i].getId() == trenchID) {
			return this->coats[i];
		}
	}
	return TrenchCoat(-1, -1, "", -1, -1, "");
}

DynamicVector<TrenchCoat> Repository::getAll() {
	// Retrieves all trench coats from the repository
	// @return: A DynamicVector containing all trench coats in the repository
	return this->coats;
}

int Repository::getSize() {
	// Gets the number of trench coats in the repository
	// @return: The number of trench coats in the repository
	return this->coats.getSize();
}

void Repository::setFileName(std::string newName)
{	//set the name of the file in which the data get's stored (database)
	//std::string newName: the new name of the file
	this->fileName = newName;
}

std::string Repository::getFileName() const
{	//get the name of the current file (database)
	//@return: the current file name
	return this->fileName;
}

void Repository::writeToFile()
{	//write into the file the information from memory in a premade way

	ofstream fout(this->fileName);
	if (fout.is_open()) {
		for (int i = 0; i < this->coats.getSize(); i++) {
			fout << this->coats[i].getId() << " ";
			fout << this->coats[i].getSize() << " ";
			fout << this->coats[i].getColour() << " ";
			fout << this->coats[i].getPrice() << " ";
			fout << this->coats[i].getQuantity() << " ";
			fout << this->coats[i].getPhotoLink() << " ";
			fout << endl;
		}
	}
	fout.close();
}

void Repository::readFromFIle()
{	//read the information from a file and store it into memory for later use

	ifstream fin(this->fileName);
	if (fin.is_open()) {
		int id, size, quantity, price;
		std::string color, link;
		while (fin >> id >> size >> color >> price >> quantity >> link) {
			TrenchCoat trench(id, size, color, price, quantity, link);
			this->coats.append(trench);
		}
	}
	fin.close();
}

Repository::Repository() {
	//constructor which automatically sets the file name

	this->fileName="trenchs.txt";
}

Repository::~Repository() {
	//destructor to clear the memory after usage
	this->coats.clear();  
}

Repository::Repository(std::string fileName)
{
	//constructor for a given filename 
	//used to read the input from the specified file

	this->fileName = fileName;
	this->readFromFIle();
}
