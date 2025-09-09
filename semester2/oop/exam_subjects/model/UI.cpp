#include "UI.h"

void UI::add()
{
    string type, date;
    cout << "enter type: ";
    cin >> type;
    cout << "enter date: ";
    cin >> date;
    if (type == "BMI") {
        double value;
        cout << "enter value: ";
        cin >> value;
        person.addAnalysis(new BMI(date, value));

    }
    else if (type == "BP") {
        int systolic, diastolic;
        cout << "enter systolic value: ";
        cin >> systolic;
        cout << "enter diastolic value: ";
        cin >> diastolic;
        person.addAnalysis(new BP(date, systolic, diastolic));
    }
    else {
        cout << "invalid type.\n";
    }
}

void UI::getAll()
{
    for (const string& s : person.getAll()) {
        cout << s << "\n";
    }
}

void UI::checkIfIll()
{
    int month;
    cout << "enter current month: ";
    cin >> month;
    if (person.isIll(month)) {
        cout << "person is ill\n";
    }
    else {
        cout << "person is not ill \n";
    }
}

void UI::saveToFile()
{
    string d1, d2, file;
    cout << "enter start date: ";
    cin >> d1;
    cout << "enter end date: ";
    cin >> d2;
    cout << "enter file name: ";
    cin >> file;
    person.writeToFile(file, d1, d2);
    cout << "saved to file";
}

void UI::menu()
{
    cout << "1. Add new analysis\n";
    cout << "2. Show all analyses\n";
    cout << "3. Check if person is ill in a given month\n";
    cout << "4. Save analyses between two dates to file\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

void UI::run()
{
    int choice;
    do {
        menu();
        cin >> choice;
        if (choice == 1) {
            add();
        }
        else if (choice == 2) {
            getAll();
        }
        else if (choice == 3) {
            checkIfIll();
        }
        else if (choice == 4) {
            saveToFile();
        }
        else if (choice == 0) {
            break;
        }
        else {
            cout << "invalid input\n";
        }

    } while (choice != 0);
}
