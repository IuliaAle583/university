#include "UI.h"
#include <iostream>

void UI::run()
{
	int option;

	while (1) {
		cout << "1. remove a client\n";
		cout << "2. show all clients and dwellings\n";
		cout << "3. add a dwelling\n";
		cout << "4. save to file\n";
		cout << "0. exit\n";
		cout << ">\n";

		cin >> option;

		if (option == 1) {
			remove();
		}
		else if (option == 2) {
			showAll();
		}
		else if (option == 3) {
			add();
		}
		else if (option == 4) {
			saveToFile();
		}
		else if (option == 0) {
			break;
		}
		else {
			cout << "Invalid option. Try again.\n";
		}
	}
}
	

void UI::remove()
{
	string name;
	cout << "enter name of the client\n";
	cin >> name;
	agency.removeClient(name);
	cout << "client removed\n";
}

void UI::add()
{
	double price;
	int prof;
	string type;
	cout << "enter type of dwelling\n";
	cin >> type;
	cout << "enter price\n";
	cin >> price;
	cout << "enter 1 if profitable, 0 otherwise\n";
	cin >> prof;
	bool p;
	if (prof == 1) {
		p = true;
	}
	else p = false;
	Dwelling d = this->agency.addDwelling(type, price, p);
	cout << "interested clients:\n";
	for (auto c : this->agency.getInterestedClients(d)) {
		cout << c->toString() << "\n";
	}

}

void UI::showAll()
{
	cout << "clients:\n";
	for (auto c : this->agency.getClients()) {
		cout << c->toString() << endl;
	}
	cout << "dwellings:\n";
	for (auto d : this->agency.getDwellings()) {
		cout << d.toString() << endl;
	}
}



void UI::saveToFile()
{
	cout << "enter filename:\n";
	string filename;
	cin >> filename;
	this->agency.writeToFile(filename);
}
