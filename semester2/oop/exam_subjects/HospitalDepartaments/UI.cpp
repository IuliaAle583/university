#include "UI.h"
#include <iostream>

void UI::run()
{
	int option;
	int found = 1;
	while (found==1) {
		cout << "1. Add new department" << endl;
		cout << "2. Show all departments" << endl;
		cout << "3. Show all efficient departments" << endl;
		cout << "4. Save to file" << endl;
		cout << "5. Remove a department" << endl;
		cout << "0. Exit" << endl;
		cin >> option;
		
		if (option == 1) {
			this->add();
		}
		else if (option == 2) {
			this->showAll();
		}
		else if (option == 3) {
			this->showAllEfficient();
		}
		else if (option == 4) {
			this->writeToFile();
		}
		else if (option == 0) {
			cout << "exiting...";
			found = 0;
		}
		else if (option == 5) {
			this->remove();
		}
		else {
			cout << "Invalid option";
		}
	}
}

void UI::add()
{
	int option;
	cout << "Enter 1 for Neonatal Unit, 2 for Surgery Department\n";
	cin >> option;
	string name;
	int nrDoctors;
	cout << "Enter the name of the hospital\n";
	cin >> name;
	cout << "Enter the number of doctors\n";
	cin >> nrDoctors;
	if (option == 1) {
		double grade;
		int mothers, newborns;
		cout << "Enter the number of mothers\n";
		cin >> mothers;
		cout << "Enter number of newborns\n";
		cin >> newborns;
		cout << "Enter average grade at birth\n";
		cin >> grade;
		this->controller.addDepartment(new NeonatalUnit(name, nrDoctors, mothers, newborns, grade));
	}
	else if (option == 2) {
		int patients;
		cout << "Enter number of patients\n";
		cin >> patients;
		this->controller.addDepartment(new Surgery(name, nrDoctors, patients));
	}
	else {
		cout << "invalid option. try again\n";
		return;
	}
}

void UI::showAll()
{
	vector<HospitalDepartment*> dep = this->controller.getAllDepartments();
	for (auto d : dep) {
		cout << d->toString() << "\n";
	}
}

void UI::showAllEfficient()
{
	vector<HospitalDepartment*> dep = this->controller.getAllEfficitentDepartments();
	for (auto d : dep) {
		cout << d->toString() << "\n";
	}
}

void UI::writeToFile()
{
	string filename;
	cout << "File name: ";
	cin >> filename;
	this->controller.writeToFile(filename);
}

void UI::remove()
{
	string name;
	cout << "Enter the name of the department to remove: ";
	cin >> name;
	this->controller.removeDepartment(name);
	cout << "successfully remeved\n";
	
}
