#include "UI.h"
#include <string>
#include <algorithm>

void UI::run()
{
	int option;
	while (1) {
		cout<< "1.Add\n2.Show\n3.Show sorted\n4.Save to file\n5.Exit\n";
		cin >> option;
		if (option == 1) this->addBuilding();
		if (option == 2) this->showAll();
		if (option == 3) this->showAllSorted();
		if (option == 4) this->saveToFile();
		if (option == 5) break;
		else {
			cout << "invalid option, try again\n";
		}
	}
}

void UI::addBuilding()
{
	int option;
	cout << "1. add flat \n2. add house\n";
	cin >> option;
	string address;
	int year;
	cout << "address:\n";
	cin.get();
	getline(cin, address);
	if (service.adressAlreadyExists(address)) {
		cout << "address already exists\n";

	}
	else {
		cout << "construction year:\n";
		cin >> year;
		if (option == 1) {
			int app,occ;
			cout << "number of apartments:\n";
			cin >> app;
			cout << "number of occupied appartments:\n";
			cin >> occ;
			//deci aici chem clasa mama
			service.addBuilding(new Block(address, year, app, occ));
		}
		else if (option == 2) {
			string type;
			bool hist;
			cout << "type:\n";
			cin >> type;
			cout << "is historic?\n";
			cin >> hist;
			service.addBuilding(new House(address, year, type, hist));
		}
		else {
			return;
		}
	}
}

void UI::showAll()
{
	vector<Building*> buildings = service.getAll();
	for (auto building : buildings) {
		cout << building->toString() << "\n";
	}
}

void UI::showAllSorted()
{
	vector<Building*> buildings = service.getAll();
	sort(buildings.begin(), buildings.end(), [](Building* a, Building* b) {
		return a->getConstructionYear() < b->getConstructionYear();
		});
	for (auto building : buildings) {
		cout << building->toString() << "\n";
	}
}

void UI::saveToFile()
{
	string file1, file2;
	cout << "1. File for restored";
	cin >> file1;
	cout << "2. File for demolished";
	cin >> file2;
	service.writeToFile(file1);
	service.writeToFileDemolished(file2);
}
