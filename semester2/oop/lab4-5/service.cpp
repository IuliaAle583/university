#include "service.h"

Service::Service() {
	// Default constructor for the Service class
	// Initializes the repository to an empty state
	this->repository = Repository();
}

Service::Service(Repository repo) {
	// Parameterized constructor for the Service class
	// @param repo: The repository object that will be used to manage trench coats
	this->repository = repo;
}

bool Service::addCoat(int trenchID, int trenchSize, const std::string& trenchColour, int trenchPrice, int trenchQuantity, const std::string& photoLink) {
	// Adds a new trench coat to the repository if the trench coat ID doesn't already exist
	// @param trenchID: The ID of the trench coat to add
	// @param trenchSize: The size of the trench coat
	// @param trenchColour: The color of the trench coat
	// @param trenchPrice: The price of the trench coat
	// @param trenchQuantity: The quantity of the trench coat
	// @param photoLink: The photo link of the trench coat
	// @return: True if the trench coat was successfully added, false if the ID already exists
	for (int i = 0; i < this->repository.getSize(); i++) {
		if (this->repository.getAll()[i].getId() == trenchID) {
			return false;
		}
	}
	this->repository.addCoat(trenchID, trenchSize, trenchColour, trenchPrice, trenchQuantity, photoLink);
	return true;
}

void Service::removeCoat(int trenchID) {
	// Removes a trench coat from the repository by its ID
	// @param trenchID: The ID of the trench coat to remove
	this->repository.removeCoat(trenchID);
}

bool Service::updateCoat(int trenchOldID, int trenchID, int trenchSize, const std::string& trenchColour, int trenchPrice, int trenchQuantity, const std::string& photoLink) {
	// Updates an existing trench coat's information if the old ID exists
	// @param trenchOldID: The old ID of the trench coat to update
	// @param trenchID: The new ID of the trench coat
	// @param trenchSize: The new size of the trench coat
	// @param trenchColour: The new color of the trench coat
	// @param trenchPrice: The new price of the trench coat
	// @param trenchQuantity: The new quantity of the trench coat
	// @param photoLink: The new photo link of the trench coat
	// @return: True if the trench coat was successfully updated, false if the old ID doesn't exist
	if (!this->checkIfExists(trenchOldID)) {
		return false;
	}
	else {
		this->repository.updateCoat(trenchOldID, trenchID, trenchSize, trenchColour, trenchPrice, trenchQuantity, photoLink);
		return true;
	}
}

int Service::checkIfExists(int trenchID) {
	// Checks if a trench coat with the given ID exists in the repository
	// @param trenchID: The ID to check
	// @return: The number of trench coats with the given ID in the repository (0 or 1 in this case)
	int nr = 0;
	for (int i = 0; i < this->repository.getSize(); i++) {
		if (this->repository.getAll()[i].getId() == trenchID) {
			nr++;
		}
	}
	return nr;
}

TrenchCoat Service::getCoat(int trenchID) {
	// Retrieves a trench coat from the repository by its ID
	// @param trenchID: The ID of the trench coat to retrieve
	// @return: The trench coat with the specified ID
	return this->repository.getCoat(trenchID);
}

const DynamicVector<TrenchCoat> Service::getAll() {
	// Retrieves all trench coats from the repository
	// @return: A DynamicVector containing all trench coats in the repository
	return this->repository.getAll();
}

int Service::getSize() {
	// Retrieves the number of trench coats in the repository
	// @return: The number of trench coats in the repository
	return this->repository.getSize();
}

Service::~Service() {
	// this->repository.clear(); 
}

DynamicVector<TrenchCoat> Service::filterBySize(int minSize) {
	//filtering the trench coats after a specified size
	//@ param minSize: the size after the filtering is done
	//@return the DynamicVector<TrenchCoat> with the filtered data

	DynamicVector<TrenchCoat> filteredCoats;
	DynamicVector<TrenchCoat> coat = this->repository.getAll();
	for (int i = 0; i < this->repository.getSize(); i++) {
		//TrenchCoat coat = this->repository.getAll()[i];
		if (coat[i].getSize() == minSize) {
			filteredCoats.append(coat[i]);
		}
	}
	return filteredCoats;
}

void Service::setFileName(std::string newName)
{	//set the file name to a specified one
	//@ param std::string newName: the new file name

	this->repository.setFileName(newName);
}

std::string Service::getFileName() const
{	// get the current file name
	//@return: the name of the file in use

	return this->repository.getFileName();
}

void Service::saveProgress()
{	//save the progress until this moment in the file

	this->repository.writeToFile();
}

void Service::loadFile()
{	// load the data from the file into the memory to access easily

	this->repository.readFromFIle();
}


