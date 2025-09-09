#include "UI.h"

void UI::run()
{
	int option;
	int ok = 1;
	while (ok == 1) {
		menu();
		cin >> option;
		if (option == 1) {
			this->add();
		}
		else if (option == 2) {
			this->showAll();
		}
		else if (option == 3) {
			this->showInefficient();
		}
		else if (option == 4) {
			this->saveToFile();
		}
		else if (option == 0) {
			ok = 0;
		}
		else {
			cout << "invalid option\n";
		}
	}
}

void UI::add()
{
	cout << "enter id\n";
	string id;
	cin >> id;
	cout << "enter 1 for refrigirator, 2 for dishwasher\n";
	int option;
	cin >> option;
	if (option == 1) {
		string elect;
		bool freezer;
		cout << "enter electricity usage class\n";
		cin >> elect;
		cout << "enter 1 if it has freezer, 0 otherwise\n";
		cin >> freezer;
		service.addAppliance(new Refrigirator(id, elect, freezer));
	}
	else if (option == 2) {
		double elec;
		cout << "enter consumed electricity for one hour\n";
		cin >> elec;
		service.addAppliance(new DishWasher(id, elec));
	}
	else {
		cout << "invalid option\n";
	}
}

void UI::showAll()
{
	vector<Appliance*> res = service.getAllAppliances();
	for (auto a : res) {
		cout << a->toString() << "\n";
	}
}

void UI::showInefficient()
{
	vector<Appliance*> res = service.getAllWithConsumedElectricityLessThan();
	for (auto a : res) {
		cout<< a->toString() << "\n";
	}
}

void UI::saveToFile()
{
	cout << "filename: \n";
	string filename;
	cin >> filename;
	int value;
	cout << "value:\n";
	cin >> value;
	service.writeToFile(filename, value);
}

void UI::menu()
{
	cout << "1. Add a new appliance." << endl;
	cout << "2. Show all" << endl;
	cout << "3. Show all inefficient" << endl;
	cout << "4. Save to a file" << endl;
	cout << ">";
}
