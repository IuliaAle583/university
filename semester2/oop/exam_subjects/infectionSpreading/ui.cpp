#include "ui.h"
#include "service.h"
#include <iostream>
using namespace std;

UI::UI(Service service) 
{
	this->service = service;
}

void UI::run()
{
	int choice;
	string name = "josh";
	service.add(name, 30, false, 101);
	name = "Alice";
	service.add(name, 25, true, 102);
	name = "BOb";
	service.add(name, 40, false, 101);
	name = "Eve";
	service.add(name, 35, false, 103);
	name = "Charile";
	service.add(name, 50, true, 103);

	while (true) {
		cout << "1. Add patient\n2. show all\n3. update\n";
		cout << "enter choice\n";
		cin >> choice;
		cin.ignore();
		if (choice == 0) {
			break;
		}
		if (choice == 1) {
			cout << "enter name: ";
			string name;
			int age, room;
			//bool infected;
			cin >> name;
			cin.ignore();
			cout << "enter age: ";
			cin >> age;
			cin.ignore();
			cout << "enter infectios: ";
			string infectedInput;
			cin >> infectedInput;
			bool infected = (infectedInput == "true" || infectedInput == "1");
			cout << "enter room nr";
			cin >> room;
			cin.ignore();
			if (service.add(name, age, infected, room)) {
				cout << "success\n";
			}
			else {
				cout << "name already exists\n";
			}

		}
		if (choice == 2) {
			DynamicVector<Patient> result = service.getAllService();
			for (int i = 0; i < result.getSize(); i++) {
				cout << result[i].getName() << " " << result[i].getAge() << " " << result[i].getInfected() << " " << result[i].getRoomNumber() << endl;
			}
		}
		if (choice == 3) {
			int age;
			cout << "enter age: ";
			cin >> age;
			cin.ignore();
			DynamicVector<Patient> result = service.updateService(age);
			for (int i = 0; i < result.getSize(); i++) {
				cout << result[i].getName() << " " << result[i].getAge() << " " << result[i].getInfected() << " " << result[i].getRoomNumber() << endl;
			}
		}
		else {
			cout << "invalid input\n";
		}
	}
}
