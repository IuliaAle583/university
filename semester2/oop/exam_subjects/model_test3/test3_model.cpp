#include "test3_model.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <algorithm>

test3_model::test3_model(Service* service, QWidget *parent)
    : QMainWindow(parent), service(service)
{
    //ui.setupUi(this);
    QWidget* central = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    listWidget = new QListWidget;
    filterCheckBox = new QCheckBox("Show only unpaid bills");
    showPaid = new QCheckBox("Show only paid bills");
    filterCheckBox->setChecked(true);
    showPaid->setChecked(true);
    companyInput = new QLineEdit;
    companyInput->setPlaceholderText("Enter company name...");
    calcButton = new QPushButton("Calculate total");
    resultLabel = new QLabel;

    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(filterCheckBox);
    mainLayout->addWidget(showPaid);
    mainLayout->addWidget(companyInput);
    mainLayout->addWidget(calcButton);
    mainLayout->addWidget(resultLabel);
    central->setLayout(mainLayout);
    setCentralWidget(central);
    setWindowTitle("Bill Manager");

    //loadBillsFromFile(R"(D:\desktop2\teste_oop\test3_model\bills.txt)");
    populateList(service->getAllBills());
    connect(filterCheckBox, &QCheckBox::stateChanged, this, &test3_model::filterBills);
    connect(showPaid, &QCheckBox::stateChanged, this, &test3_model::filterBills);
    connect(calcButton, &QPushButton::clicked, this, &test3_model::calculateTotal);
}


void test3_model::calculateTotal()
{
    QString company = companyInput->text().trimmed();
    double total = service->calculateTotalUnpaidForCompany(company);
    if (total == 0) {
        QMessageBox::warning(this, "Error", "No unpaid bills for this company");
        resultLabel->setText("");
    }
    else {
        resultLabel->setText("Total unpaid: " + QString::number(total));
    }
}

void test3_model::populateList(const std::vector<Bill>& bills)
{
    listWidget->clear();
    for (const Bill& bill : bills) {
        QString itemText = bill.company + " - " + QString::number(bill.sum);
        QListWidgetItem* item = new QListWidgetItem(itemText);
        if (!bill.isPaid) {
            item->setBackground(Qt::red);
        }
        listWidget->addItem(item);
    }
}

void test3_model::filterBills() {
    bool paid = showPaid->isChecked();
    bool unpaid = filterCheckBox->isChecked();
    auto filtered = service->filterBills(paid, unpaid);
    populateList(filtered);
}

test3_model::~test3_model()
{}
