#include "service.h"
#include <QFile>
#include <QTextStream>
#include <algorithm>

void Service::loadBillsFromFile(const QString& fileName)
{
    bills.clear();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Ideally throw exception or handle error somewhere else
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(';');
        if (parts.size() == 4) {
            Bill bill(parts[0], parts[1], parts[2].toDouble(), parts[3].trimmed() == "true");
            bills.push_back(bill);
        }
    }
    std::sort(bills.begin(), bills.end(), [](const Bill& a, const Bill& b) {
        return a.company < b.company;
        });
}


std::vector<Bill> Service::getAllBills() const
{
    return bills;
}

std::vector<Bill> Service::filterBills(bool showPaid, bool showUnpaid) const
{
    std::vector<Bill> filtered;
    for (const Bill& bill : bills) {
        if (bill.isPaid && showPaid) filtered.push_back(bill);
        if (!bill.isPaid && showUnpaid) filtered.push_back(bill);
    }
    return filtered;
}

double Service::calculateTotalUnpaidForCompany(const QString& company) const
{
    double total = 0;
    for (const Bill& bill : bills) {
        if (!bill.isPaid && bill.company.compare(company, Qt::CaseInsensitive) == 0) {
            total += bill.sum;
        }
    }
    return total;
}
