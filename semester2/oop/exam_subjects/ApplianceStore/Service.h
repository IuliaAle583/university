#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Appliance.h"
using namespace std;

class Service
{
private:
	vector<Appliance*> appliances;
public:
	void addAppliance(Appliance* a);
	vector<Appliance*> getAllAppliances();
	vector<Appliance*> getAllWithConsumedElectricityLessThan();
	void writeToFile(string filename, double value);
	vector<Appliance*> getSorted(double value);
	~Service();
	Service();

};

