#pragma once
#include "domain.h"
#include "dynamicVector.h"
#include <algorithm>

class Repository {
private:
	Vector<Bill> bills;
public:
	Repository() = default;
	bool addBill(const Bill& bill);
	Vector<Bill> getAllBillsSorted();
	Vector<Bill> getPaidBills();
	double getTotalPaidBills();
};