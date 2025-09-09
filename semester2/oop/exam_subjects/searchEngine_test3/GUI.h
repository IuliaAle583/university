#pragma once
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "Service.h"

class GUI :public QWidget
{
private:
	Service service;
	QListWidget* mainItems,*keywordList;
	QLineEdit* inputField;
	QPushButton* showBestMatch;
public:
	GUI(QWidget* parent = Q_NULLPTR);
	~GUI() = default;
	void populateList();
	//void showDocuments();
public slots:
	void onChangeText();
	void bestMatch();
};

