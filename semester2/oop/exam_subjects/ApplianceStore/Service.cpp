#include "Service.h"
#include "Appliance.h"

void Service::addAppliance(Appliance* a)
{
	appliances.push_back(a);
}

vector<Appliance*> Service::getAllAppliances()
{
	return appliances;
}

vector<Appliance*> Service::getAllWithConsumedElectricityLessThan()
{
	vector<Appliance*> res;
	for (auto a : appliances) {
		if (a->consumedElectricity() > 100) {
			res.push_back(a);
		}

	}
	return res;
}

void Service::writeToFile(string filename, double value)
{
	ofstream fout(filename);
	vector<Appliance*> sorted = getSorted(value);
	for (auto a : appliances) {
		fout << a->toString() << "\n";
	}
	fout.close();
}

vector<Appliance*> Service::getSorted(double value)
{
	vector<Appliance*> res;
	for (auto a : appliances) {
		if (a->consumedElectricity() < value)
			res.push_back(a);
	}
	sort(res.begin(), res.end(), [](Appliance* a, Appliance* b) {return a->getId() < b->getId(); });
	return res;
}

Service::~Service()
{
	for (auto a : appliances) {
		delete a;
	}
}

Service::Service()
{
	Appliance* refrigerator1 = new Refrigirator("1a", "A", true);
	Appliance* refrigerator2 = new Refrigirator("1b", "A+", true);
	Appliance* refrigerator3 = new Refrigirator("1aa", "A+", true);

	Appliance* dishwasher1 = new DishWasher("2a", 20);
	Appliance* dishwasher2 = new DishWasher("2b", 50);

	appliances.push_back(refrigerator1);
	appliances.push_back(refrigerator2);
	appliances.push_back(dishwasher1);
	appliances.push_back(dishwasher2);
	appliances.push_back(refrigerator3);
}
