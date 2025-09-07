#include "UI.h"

void UI::printMenu() const
{
	cout << "1. add car.\n";
	cout << "2. show all cars\n";
	cout << "3. save to file\n";
	cout << ">";
}

void UI::start()
{
	int option;
	while (1) {
		printMenu();
		cin >> option;
		if (option == 1) {
			add();
		}
		else if (option == 2) {
			show();
		}
		else if (option == 3) {
			saveFile();
		}
		else if (option == 0) break;
		else cout << "invalid option";
	}
}

void UI::add()
{
	string engineType;
	int nrDoors;
	int autonomy = 0;

	cout << "Enter number of doors (2 or 4) ";
	cin >> nrDoors;
	cout << "Enter engine type (Turbo / Electric): ";
	cin >> engineType;

	if (engineType == "Electric") {
		cout << "Enter autonomy: ";
		cin >> autonomy;
	}

	service.addCar(nrDoors, engineType, autonomy);
	Car* last = service.getAll().back();
	cout << "Car was added. It's data is:\n";
	cout << last->toString() << endl;

}

void UI::show()
{
	for (auto* car : service.getAll())
		cout << car->toString() << endl;
}

void UI::saveFile()
{
	double maxPrice;
	string filename;
	cout << "Enter max price: ";
	cin >> maxPrice;
	cout << "Enter file name: ";
	cin >> filename;
	service.writeToFile(filename, maxPrice);
	cout << "Cars saved to file.\n";
}
