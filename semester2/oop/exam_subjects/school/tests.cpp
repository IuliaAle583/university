#include <iostream>
#include <cassert>
#include "repository.h"

void testAddBill() {
    Repository repo;

    Bill b1("1234AB", "Digi", true, 100.0);
    assert(repo.addBill(b1) == true); 

    assert(repo.addBill(b1) == false); 

    Bill b2("5678CD", "Enel", false, 50.0);
    assert(repo.addBill(b2) == true);  

    assert(repo.getAllBillsSorted().getSize() == 2);

    Bill b3("9999ZZ", "Vodafone", true, 75.5);
    assert(repo.addBill(b3) == true);
    Bill b4("1111YY", "Orange", false, 30.0);
    assert(repo.addBill(b4) == true);

    assert(repo.getAllBillsSorted().getSize() == 4);

    std::cout << "All addBill tests passed successfully!\n";
}

void testGetTotalPaidBills() {
    Repository repo;

    assert(repo.getTotalPaidBills() == 0.0);

    repo.addBill(Bill("1234", "Digi", false, 100.0));
    repo.addBill(Bill("5678", "Enel", false, 50.0));
    assert(repo.getTotalPaidBills() == 0.0);

    repo.addBill(Bill("9999", "Vodafone", true, 75.5));
    repo.addBill(Bill("1111", "Orange", true, 30.0));
    assert(repo.getTotalPaidBills() == 75.5 + 30.0);

    repo.addBill(Bill("2222", "UPC", true, 45.0));
    assert(repo.getTotalPaidBills() == 75.5 + 30.0 + 45.0);

    std::cout << "All getTotalPaidBills tests passed successfully!\n";
}


void callAllTests() {
    testAddBill();
    testGetTotalPaidBills();
}