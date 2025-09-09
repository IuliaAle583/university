#pragma once
#include <vector>
#include <QString>
#include "domain.h"
class Service {
public:
    void loadBillsFromFile(const QString& fileName);
    std::vector<Bill> getAllBills() const;
    std::vector<Bill> filterBills(bool showPaid, bool showUnpaid) const;
    double calculateTotalUnpaidForCompany(const QString& company) const;

private:
    std::vector<Bill> bills;
};