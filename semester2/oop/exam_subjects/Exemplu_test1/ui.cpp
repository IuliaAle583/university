#include "ui.h"
#include <iostream>

void UI::menu()
{
    std::cout << "\nCar Manager Menu:\n";
    std::cout << "1. Add a new car\n";
    std::cout << "2. Remove a car by year\n";
    std::cout << "3. Show all cars (sorted by manufacturer and model)\n";
    std::cout << "4. Show all vintage cars (older than 45 years, sorted by color)\n";
    std::cout << "0. Exit\n";
}

void UI::addCar()
{
    std::string name, model, color;
    int year;

    std::cout << "Enter manufacturer: ";
    std::cin >> name;
    std::cout << "Enter model: ";
    std::cin >> model;
    std::cout << "Enter year: ";
    std::cin >> year;
    std::cout << "Enter color: ";
    std::cin >> color;

    if (service.addCar(Car(name, model, year, color))) {
        std::cout << "car added successfully\n";
    }
    else {
        std::cout << "car already exists!\n";
    }
}

void UI::removeCar()
{
    int year;
    std::cout << "enter car to remove (year)";
    std::cin >> year;
    if (service.removeCar(year)) {
        std::cout << "car removed successfully\n";
    }
    else {
        std::cout << "car not found\n";
    }
}

void UI::showAllCars()
{
    int size;
    Car* cars = service.getAllCarsSorted(size);
    for (int i = 0; i < size; i++) {
        std::cout << cars[i].get_name() << " | " << cars[i].get_model() << " | "
            << cars[i].get_year() << " | " << cars[i].get_color() << "\n";
    }
    delete[] cars; 
}

void UI::showVintageCars()
{
    int size;
    Car* cars = service.getVintageCarsSorted(size);
    for (int i = 0; i < size; i++) {
        std::cout << cars[i].get_name() << " | " << cars[i].get_model() << " | "
            << cars[i].get_year() << " | " << cars[i].get_color() << "\n";

    }
    delete[] cars;
}

UI::UI(Service& service): service(service){}

void UI::run()
{
    int option;
    do {
        menu();
        std::cout << "Choose an option: ";
        std::cin >> option;
        switch (option) {
        case 1: addCar(); break;
        case 2: removeCar(); break;
        case 3: showAllCars(); break;
        case 4: showVintageCars(); break;
        case 0: std::cout << "exiting\n"; break;
        default: std::cout << "invalid option\n";
        }
    } while (option != 0);
}
