#include "Service.h"
#include <fstream>

void Service::addBuilding(Building* b)
{
	buildings.push_back(b);
}

void Service::writeToFile(string file)
{
	ofstream fout(file);
	for (auto building : buildings) {
		if (building->mustBeRestored()) {
			fout << building->toString()<<"\n";
		}
	}
}

void Service::writeToFileDemolished(string file)
{
	ofstream fout(file);
	for (auto building : buildings) {
		if (building->canBeDemolished()) {
			fout << building->toString()<<"\n";
		}
	}
}
