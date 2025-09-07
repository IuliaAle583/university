#pragma once
#include <string>

class TrenchCoat {
private:
	int id;
	int size;
	std::string colour;
	int price;
	int quantity;
	std::string link;

public:
	TrenchCoat();
	TrenchCoat(int trenchID, int sizeTrench, const std::string& trenchColour, int trenchPrice, int trenchQuantity, const std::string& linkPhoto);
	int getId();
	int getSize();
	std::string getColour() const;
	int getPrice();
	int getQuantity();
	std::string getPhotoLink() const;

	bool operator ==(const TrenchCoat& trench);
	void setID(int newID);
	void setSize(int newSize);
	void setColour(const std::string& newColour);
	void setPrice(int newPrice);
	void setQuantity(int newQuantity);
	void setPhotoLink(const std::string& newPhotoLink);
};