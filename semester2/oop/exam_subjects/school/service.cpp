#include "service.h"

bool Service::addBill(const std::string& serial, const std::string& company, bool isPaid, double sum)
{
	Bill newBill(serial, company, isPaid, sum);
	return repo.addBill(newBill);
}

Vector<Bill> Service::getAllBillsSorted()
{
	return repo.getAllBillsSorted();
}

Vector<Bill> Service::getPaidBills()
{
	return repo.getPaidBills();
}

double Service::getTotalPaidBills()
{
	return repo.getTotalPaidBills();
}
