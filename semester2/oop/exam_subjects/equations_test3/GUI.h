#pragma once
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "Service.h"

class GUI :public QWidget
{
private:
	Service service;
	QListWidget* mainItems;
	QLineEdit* a, * b, * c, *solutionDisplay;
	QPushButton* add;
	QPushButton* computeSolution;
public:
	GUI(QWidget* parent = Q_NULLPTR);
	~GUI() = default;
	void populateItems();
public slots:
	void populateFields();
	void addEquation();
	void showSolution();

};

