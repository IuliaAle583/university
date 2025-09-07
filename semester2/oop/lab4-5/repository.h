#pragma once
#include <string>
#include "domain.h"
#include "dynamicVector.h"

class Repository {
private:
	DynamicVector<TrenchCoat> coats;
	std::string fileName;
public:
	Repository();
	~Repository();
	Repository(std::string fileName);

	void addCoat(int trenchID, int trenchSize, const std::string& trenchColour, int trenchPrice, int trenchQuantity, const std::string& photoLink);
	void removeCoat(int ID);
	void updateCoat(int trenchOldID, int trenchID, int trenchSize, const std::string& trenchColour, int trenchPrice, int trenchQuantity, const std::string& photoLink);
	bool validID(int trenchID);
	TrenchCoat getCoat(int trenchID);
	DynamicVector<TrenchCoat> getAll();
	int getSize();
	void setFileName(std::string newName);
	std::string getFileName() const;
	void writeToFile();
	void readFromFIle();
};
