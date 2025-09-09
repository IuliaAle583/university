#include "ui.h"
#include <iostream>

void UI::printMenu() const
{
    std::cout << "\n1. Add Bill\n";
    std::cout << "2. Show All Bills (Sorted by Company)\n";
    std::cout << "3. Show Paid Bills & Total Paid Amount\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

void UI::run()
{
    int option;
    do {
        printMenu();
        std::cin >> option;
        if (option == 1) {
            addBill();
        }
        else if (option == 2) {
            showAllBills();
        }
        else if (option == 3) {
            showPaidBills();
        }
    } while (option != 0);
}

void UI::addBill()
{
    std::string serial, company;
    double sum;
    bool isPaid;
    std::cout << "Enter Serial Number: "; std::cin >> serial;
    std::cout << "Enter Company Name: "; std::cin >> company;
    std::cout << "Enter Amount: "; std::cin >> sum;
    std::cout << "Is Paid (1 = true, 0 = false): "; std::cin >> isPaid;
    if (service.addBill(serial, company, isPaid, sum)) {
        std::cout << "bill was added\n";
    }
    else {
        std::cout << "bill already exists\n";
    }
}

void UI::showAllBills()
{
    Vector<Bill> bills = service.getAllBillsSorted();
    for (int i = 0; i < bills.getSize(); i++) {
        const Bill& bill = bills[i];
        std::cout<< bill.getName() << " | " << bill.getNumber()
            << " | " << bill.getSum() << " | "
            << (bill.getPaid() ? "Paid" : "Unpaid") << "\n";
    }
}

void UI::showPaidBills()
{
    Vector<Bill> paidBilld = service.getPaidBills();
    double total = service.getTotalPaidBills();
    for (int i = 0; i < paidBilld.getSize(); i++) {
        const Bill& bill = paidBilld[i];
        std::cout << bill.getName() << " | " << bill.getNumber()
            << " | " << bill.getSum() << "\n";
    }
    std::cout << "the total is: " << total << "\n";
   
}
