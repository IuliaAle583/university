#pragma once
#include "Service.h"
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout> // cu asta le asez pe verticala (orientarea)
//deci folosesc qv cand vreau sa am butoanele unul sub altul si qh cand sa fie unul langa altul
class GUI :public QWidget
{
private:
	Service service;
	QListWidget* billsWidget;
	QCheckBox* sortBills;
	QLabel* userInputLabel;
	QLineEdit* userInput;
	QPushButton* calculateTotal;
	QLabel* totalLabel;
	QLineEdit* total;
	QCheckBox* paid;
public:
	GUI(QWidget* parent = Q_NULLPTR);
	void load();
public slots:
	void loadSortedBills();
	void showAmount();
	void showOnlyPaid();
};

