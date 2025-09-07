#include "ui.h"
#include <iostream>

UI::UI(Service& service) : service(service) {}

void UI::showMenu() {
    cout << "1. Show all schools" << endl;
    cout << "2. Remove a school" << endl;
    cout << "3. Mark schools visited before a given date\n";
    cout << "4. Show schools to be visited after a given date\n";
    cout << "5. Exit" << endl;
}

void UI::handleShowAllSchools() {
    DynamicVector<School> schools = service.showAllSchools();

    for (int i = 0; i < schools.getSize(); i++) {
        School school = schools[i];
        cout << "Name: " << school.getName() << ", "
            << "Address: " << school.getAddress() << ", "
            << "Date: " << school.getDate().day << "/"
            << school.getDate().month << "/" << school.getDate().year << ", "
            << "Active: " << (school.getValue() ? "Yes" : "No") << endl;
    }
}

void UI::markSchoolsVisitedBefore() {
    std::string dateStr;
    std::cout << "Enter date (DD/MM/YYYY): ";
    std::cin >> dateStr;

    Date date = parseDate(dateStr);  
    DynamicVector<School> schools = service.showAllSchools();

    for (int i = 0; i < schools.getSize(); i++) {
        if (schools[i].getDate() < date) {
            schools[i].setValue(true);  
            std::cout << "Marked " << schools[i].getName() << " as visited.\n";
        }
    }
}

void UI::showSchoolsToBeVisitedAfter() {
    std::string dateStr;
    std::cout << "Enter date (DD/MM/YYYY): ";
    std::cin >> dateStr;

    Date date = parseDate(dateStr);  
    DynamicVector<School> schoolsToVisit = service.showSchoolsToBeVisitedAfterDate(date);

    if (schoolsToVisit.getSize() > 0) {
        std::cout << "Schools to be visited after " << date.day << "/" << date.month << "/" << date.year << ":\n";
        for (int i = 0; i < schoolsToVisit.getSize(); i++) {
            School school = schoolsToVisit[i];
            std::cout << "Name: " << school.getName() << ", "
                << "Address: " << school.getAddress() << ", "
                << "Date: " << school.getDate().day << "/"
                << school.getDate().month << "/" << school.getDate().year << ", "
                << "Active: " << (school.getValue() ? "Yes" : "No") << std::endl;
        }
    }
    else {
        std::cout << "No schools to be visited after this date.\n";
    }
}

void UI::removeSchool() {
    std::string name, address;

    std::cout << "Name: ";
    std::cin.ignore(); 
    std::getline(std::cin, name);

    std::cout << "Address: ";
    std::getline(std::cin, address);

    bool success = service.removeService(name, address);

    if (success) {
        std::cout << "Success.\n";
    }
    else {
        std::cout << "Not found.\n";
    }
}

void UI::run() {
    bool running = true;
    while (running) {
        showMenu();
        int option;
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
        case 1:
            handleShowAllSchools();  
            break;
        case 2:
            removeSchool();
            break;
        case 3:
            markSchoolsVisitedBefore();
            break;
        case 4:
            showSchoolsToBeVisitedAfter();
            break;
        case 5:
            running = false;
            break;
        default:
            cout << "Invalid option. Try again." << endl;
        }
    }
}

