#pragma once
#include "repository.h"

class Service {
private:
	Repository repo;
public:
	Service() = default;
	bool addBill(const std::string& serial, const std::string& company, bool isPaid, double sum);
	Vector<Bill> getAllBillsSorted();
	Vector<Bill> getPaidBills();
	double getTotalPaidBills();

};
