#pragma once
#include <string>
using namespace std;
class Appliance
{
protected:
	string id;
public:
	virtual double consumedElectricity() = 0;
	virtual string toString();
	Appliance(string id) : id(id) {};
	~Appliance() = default;
	string getId() { return id; };
};

class Refrigirator :public Appliance {
private:
	string electricityUsageClass;
	bool hasFreezer;
public:
	double consumedElectricity() override;
	string toString() override;
	Refrigirator(string id, string usage, bool freezer) : Appliance(id), electricityUsageClass(usage), hasFreezer(freezer) {};
	~Refrigirator() = default;

};

class DishWasher :public Appliance {
private:
	double consumedElectricityForOneHour;
public:
	double consumedElectricity() override;
	string toString() override;
	DishWasher(string id, double elect) : Appliance(id), consumedElectricityForOneHour(elect) {};
	~DishWasher() = default;
};

