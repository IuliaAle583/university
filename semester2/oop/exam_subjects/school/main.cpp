// school.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ui.h"
#include "tests.h"

int main()
{
    Service service;
    service.addBill("0A33455X", "Digi Sport", false, 75.00);
    service.addBill("EED36677", "E-On", true, 122.00);
    service.addBill("X990TTRR", "Orange", true, 46.00);
    service.addBill("1234RR55", "Vodafone", false, 23.00);
    service.addBill("TRE3EERR", "Tcomm", true, 10.00);
    service.addBill("GH5678YY", "Electrica", true, 89.99);
    service.addBill("ZZ1234PP", "Apa Nova", false, 54.00);
    service.addBill("BGT56677", "UPC", true, 111.50);
    service.addBill("MNB33221", "Netflix", false, 29.99);
    service.addBill("LOP87654", "HBO", true, 99.00);
    UI ui(service);
    ui.run();
    callAllTests();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
