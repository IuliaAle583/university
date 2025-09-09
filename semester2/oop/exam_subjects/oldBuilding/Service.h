#pragma once
#include "domain.h"
#include <vector>
class Service
{
private:
	vector<Building*> buildings;
public:
	void addBuilding(Building* b);
	vector<Building*> getAll() { return this->buildings; };
	bool adressAlreadyExists(string address) {
		for (auto building : buildings) {
			if (building->getAddress() == address) return true;
		}
		return false;
	}
	void writeToFile(string file);
	void writeToFileDemolished(string file);

	Service() {
		Building* house1 = new House("str asda", 2202, "casa", true);
		Building* house2 = new House("str 2da3a", 2012, "casa", true);

		Building* flat1 = new Block("str dwa", 2022, 22, 23);
		Building* flat2 = new Block("str aaaa", 2105, 5, 10);

		buildings.push_back(flat1);
		buildings.push_back(flat2);
		buildings.push_back(house1);
		buildings.push_back(house2);

	}

	~Service() {
		for (auto building : buildings) {
			delete building;
		}
	}

};

/*
 De ce vector<Building*> ?i nu vector<Building>?
Dac? ai folosi vector<Building>, ai avea urm?toarele probleme:
Obiectele de tip Block sau House ar fi slicing-uite (s-ar p?stra doar partea de Building, iar metodele virtuale nu s-ar comporta polimorfic).
Ai pierde complet comportamentul specific claselor derivate (metodele suprascrise precum toString(), mustBeRestored() etc.).

Avantajele lui vector<Building*>:
Permite stocarea oric?rui tip de cl?dire (Block, House), într-un singur container.
Po?i apela metode virtuale (b->toString(), b->canBeDemolished()), iar C++ va ?ti s? apeleze implementarea corect?, chiar dac? b e de tip Building*
*/

