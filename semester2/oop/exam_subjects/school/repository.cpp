#include "repository.h"

bool Repository::addBill(const Bill& bill)
{
	for (int i = 0; i < bills.getSize(); i++) {
		if (bills[i].getNumber() == bill.getNumber()) {
			return false;
		}
	}
	bills.append(bill);
	return true;
}

Vector<Bill> Repository::getAllBillsSorted()
{
	Vector<Bill> sortedBills = bills;
	std::sort(sortedBills.begin(), sortedBills.end(),
		[](const Bill& a, const Bill& b) { return a.getName() < b.getName(); });
	return sortedBills;
}


Vector<Bill> Repository::getPaidBills()
{
	Vector<Bill> paidBills;
	for (int i = 0; i < bills.getSize(); i++) {
		if (bills[i].getPaid()) {
			paidBills.append(bills[i]);
		}
	}
	return paidBills;
}

double Repository::getTotalPaidBills()
{
	double total = 0;
	for (int i = 0; i < bills.getSize(); i++) {
		if (bills[i].getPaid()) {
			total += bills[i].getSum();
		}
	}
	return total;
}
