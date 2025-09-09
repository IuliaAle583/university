#pragma once
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "observer.h"
#include "session.h"

class GUI:public QWidget, public Observer
{
	//do not forget about observer here!!
private:
	Session& session;
	int userId;
	QListWidget* itemsList;
	QListWidget* offersList;
	QComboBox* comboBox;
	QPushButton* addButton;
	QLineEdit* nameEdit, * categoryEdit, * priceEdit,*offerEdit;
public:
	GUI(Session& session, int userId, QWidget* parent = Q_NULLPTR);
	~GUI() override = default;
	void update()const override;
public slots:
	void addItem();
	void selectItem();
};

