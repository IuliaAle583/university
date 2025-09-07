#pragma once
#include <string>
#include "repository.h"

class Service {
private:
	Repository repository;
public:
	Service();
	Service(Repository repo);
	bool addCoat(int trenchID, int trenchSize, const std::string& trenchColour, int trenchPrice, int trenchQuantity, const std::string& photoLink);
	void removeCoat(int trenchID);
	bool updateCoat(int trenchOldID, int trenchID, int trenchSize, const std::string& trenchColour, int trenchPrice, int trenchQuantity, const std::string& photoLink);
	int checkIfExists(int trenchID);
	TrenchCoat getCoat(int trenchID);
	const DynamicVector<TrenchCoat> getAll();
	//DynamicVector<TrenchCoat> filterBySize(int trenchSize);
	int getSize();
	~Service();
	DynamicVector<TrenchCoat> filterBySize(int minSize);
	void setFileName(std::string newName);
	std::string getFileName() const;
	void saveProgress();
	void loadFile();
};
