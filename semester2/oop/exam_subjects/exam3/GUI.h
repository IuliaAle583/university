#pragma once
#include "Service.h"
#include "model.h"
#include <QWidget>
#include <utility> //!!!!!!!
#include <QTableView> //!!!!!!!1
#include <QCheckBox>
#include <QSortFilterProxyModel> //!!!!!!!!!
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>

class GUI:public QWidget
{
	Q_OBJECT
private:
	QCheckBox* constellations{};	//pot si fara {} sau sa ii dau nullptr, same shit
	Astronomer astronomer;
	Service& service;
	QTableView* table;	//ca un container
	Model* starsModel;	// datele direct de la mama natura
	QSortFilterProxyModel* model;	//cu tot cu filtrari
	//le folosesc pe ambele ca sa nu imi schimbe tabelul initial cand fac filtrari/ sortari
	QLineEdit* nameEdit, * raEdit, * decEdit, * starNameFilter, * diameterEdit;
	QPushButton* addStarButton;
	QListWidget* filteredStars;
public:
	GUI(Astronomer astr, Service& service, Model* model);
public slots:
	void setUp();
	void showConstellations();
	void addStar();
	void populateList();
	void viewStar();

};

