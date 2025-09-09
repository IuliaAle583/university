#include "GUI.h"
#include <QMessageBox>	//pentru mesajul de eroare

GUI::GUI(QWidget* parent) :QWidget(parent)
{
	this->setWindowTitle("Bills");
	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->billsWidget = new QListWidget;
	//this->sortBills = new QPushButton("Sort the bills");
	this->sortBills = new QCheckBox("show only unpaid bills");
	this->userInputLabel = new QLabel("Enter the name of the company");
	this->userInput = new QLineEdit;
	this->calculateTotal = new QPushButton("Calculate amount of bills");
	this->totalLabel = new QLabel("Total amount");
	this->total = new QLineEdit;
	this->paid = new QCheckBox("show only paid");
	mainLayout->addWidget(billsWidget);
	mainLayout->addWidget(sortBills);
	mainLayout->addWidget(paid);
	mainLayout->addWidget(userInputLabel);
	mainLayout->addWidget(userInput);
	mainLayout->addWidget(calculateTotal);
	mainLayout->addWidget(totalLabel);
	mainLayout->addWidget(total);
	this->setLayout(mainLayout);
	this->loadSortedBills();
	QObject::connect(this->sortBills, &QCheckBox::stateChanged, this, &GUI::loadSortedBills); //atentie sa nu fie paranteze la functie
	QObject::connect(this->paid, &QCheckBox::toggled, this, &GUI::showOnlyPaid);
	QObject::connect(this->calculateTotal, &QPushButton::clicked, this, &GUI::showAmount);
}

void GUI::load()
{
	this->billsWidget->clear();
	for (auto bill : this->service.getAllService()) {
		this->billsWidget->addItem(QString::fromStdString(bill.toString()));
	}
}

void GUI::showAmount()
{
	string company = this->userInput->text().toStdString();
	double total = this->service.billsByCompany(company);
	if (total == 0.0) {
		QMessageBox::warning(this, "Error", "There are no unpaid bills for this company");
		this->total->clear();
	}
	else {
		this->total->setText(QString::number(total));
	}
	//this->total->setText(QString::number(this->service.billsByCompany(company)));
}

void GUI::showOnlyPaid()
{
	this->billsWidget->clear();

	bool filterPaid = this->paid->isChecked();

	for (auto bill : this->service.getAllSorted()) {
		if (filterPaid && !bill.getIsPaid()) {
			continue;
		}

		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(bill.toString()));
		if (!bill.getIsPaid()) {
			item->setBackground(Qt::red);
		}
		this->billsWidget->addItem(item);
	}
}

void GUI::loadSortedBills() {
	this->billsWidget->clear();

	bool filterUnpaid = this->sortBills->isChecked();

	for (auto bill : this->service.getAllSorted()) {
		if (filterUnpaid && bill.getIsPaid()) {
			continue;  
		}

		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(bill.toString()));

		if (!bill.getIsPaid()) {
			item->setBackground(Qt::red);
		}

		this->billsWidget->addItem(item);
	}
}