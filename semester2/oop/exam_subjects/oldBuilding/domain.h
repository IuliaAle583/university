#pragma once
#include <string>
using namespace std;

class Building
{
protected:
	string address;
	int constructionYear;
public:
	Building(string address, int constructionYear) : address{ address }, constructionYear{ constructionYear } {};
	virtual bool mustBeRestored() { return false; };
	virtual bool canBeDemolished() { return false; };
	virtual string toString();
	string getAddress() { return this->address; };
	int getConstructionYear() { return this->constructionYear; };
};

class Block : public Building {
private:
	int totalApartments;
	int occupiedApartments;
public:
	Block(string address, int constructionYear, int totalApartments, int occupiedApartments) :
		Building{ address, constructionYear }, totalApartments{ totalApartments }, occupiedApartments{ occupiedApartments } {};

	bool mustBeRestored() override;
	bool canBeDemolished() override;
	string toString() override;

};

class House : public Building {
private:
	string type;
	bool isHistorical;
public:
	House(string address, int constructionYear, string type, bool isHistorical) :
		Building{ address, constructionYear }, type{ type }, isHistorical{ isHistorical } {};
	bool mustBeRestored() override;
	bool canBeDemolished() override;
	string toString() override;
};
