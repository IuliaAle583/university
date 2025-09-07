#include <iostream>
#include <string>
#include "domain.h"

TrenchCoat::TrenchCoat() {
	// Default constructor that initializes a TrenchCoat object with default values
	// id, size, price, quantity are set to 0, and colour and link are set to "0"
	this->id = 0;
	this->size = 0;
	this->colour = "0";
	this->price = 0;
	this->quantity = 0;
	this->link = "0";
};

TrenchCoat::TrenchCoat(int trenchID, int sizeTrench, const std::string& trenchColour, int trenchPrice, int trenchQuantity, const std::string& linkPhoto) {
	// Parameterized constructor that initializes a TrenchCoat object with given values
	// trenchID: set the coat's unique identifier (id)
	// sizeTrench: the coat's size
	// trenchColour: sets the coat's colour
	// trenchPrice: sets the price of the coat
	// trenchQuantity: sets the number of items available
	// linkPhoto: sets the link to the image of the coat
	this->id = trenchID;
	this->size = sizeTrench;
	this->colour = trenchColour;
	this->price = trenchPrice;
	this->quantity = trenchQuantity;
	this->link = linkPhoto;
}

int TrenchCoat::getId() {
	// Returns the unique identifier (id) of the TrenchCoat
	// Return type: int
	return this->id;
}

int TrenchCoat::getSize() {
	// Returns the size of the TrenchCoat
	// Return type: int
	return this->size;
}

int TrenchCoat::getPrice() {
	// Returns the price of the TrenchCoat
	// Return type: int
	return this->price;
}

int TrenchCoat::getQuantity() {
	// Returns the quantity of the TrenchCoat available
	// Return type: int
	return this->quantity;
}
std::string TrenchCoat::getColour() const {
	// Returns the colour of the TrenchCoat
	// Return type: std::string (colour)
	return this->colour;
}
std::string TrenchCoat::getPhotoLink() const {
	// Returns the photo link of the TrenchCoat
	// Return type: std::string (link)
	return this->link;
}

void TrenchCoat::setID(int newID) {
	// Sets the unique identifier (id) of the TrenchCoat.
	// Parameter: newID (int) - new ID to set for the coat.
	this->id = newID;
}

void TrenchCoat::setSize(int newSize) {
	// Sets the size of the TrenchCoat.
	// Parameter: newSize (int) - new size to set for the coat.
	this->size = newSize;
}

void TrenchCoat::setPrice(int newPrice) {
	// Sets the price of the TrenchCoat.
	// Parameter: newPrice (int) - new price to set for the coat.
	this->price = newPrice;
}

void TrenchCoat::setQuantity(int newQuantity) {
	// Sets the quantity of the TrenchCoat available.
	// Parameter: newQuantity (int) - new quantity to set for the coat.
	this->quantity = newQuantity;
}

void TrenchCoat::setPhotoLink(const std::string& newPhotoLink) {
	// Sets the photo link of the TrenchCoat.
	// Parameter: newPhotoLink (std::string) - new link to set for the coat's photo.
	this->link = newPhotoLink;
}

void TrenchCoat::setColour(const std::string& newColour) {
	// Sets the colour of the TrenchCoat.
	// Parameter: newColour (std::string) - new colour to set for the coat.
	this->colour = newColour;
}

bool TrenchCoat::operator ==(const TrenchCoat& trench) {
	// Checks if two TrenchCoat objects are equal based on their attributes.
	// Compares id, size, price, quantity, and link.
	// Parameter: trench (TrenchCoat) - the TrenchCoat object to compare with.
	// Return type: bool - returns true if both objects are equal, false otherwise.
	if (this->id == trench.id &&
		this->size == trench.size &&
		this->price == trench.price &&
		this->quantity == trench.quantity &&
		this->link == trench.link) {
		return true;
	}
	return false;
}