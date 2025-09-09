#include "Service.h"

vector<Bill> Service::getAllSorted()
{
    vector<Bill> bills = this->getAllService();
    sort(bills.begin(), bills.end());
    return bills;
}

double Service::billsByCompany(string name)
{
    double total=0.0;   //daca nu ii dau o valoare nu merge
    for (auto bill : this->repo.getAll()) {
        if (bill.getCompanyName() == name && !bill.getIsPaid())
            total += bill.getSum();
    }
    return total;
}
