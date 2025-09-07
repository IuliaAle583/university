#pragma once
#include "service.h"
#include "validator.h"
#include "AdminGUI.h"
#include "ShoppingBasket.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QComboBox>
#include <QMainWindow>
#include <QVBoxLayout>
using namespace std;

class GUI : public QMainWindow
{
Q_OBJECT
private:
	string type = "empty";
	Service& service;
	ShoppingBasket* shBasket;
	void initGUI();
	QComboBox* filetypeBox;
	QPushButton* adminButton, * saveButton, *userButton;
public:
	GUI(Service& s, QWidget* p = 0);
	~GUI();
	void signalsAndSlots();
	void AdminModeGUI();
	void saveFileType();
	void UserModeGUI();

};

