#pragma once
#include "Service.h"
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class GUI :public QWidget
{
private:
	Service service;
	QListWidget* mainItems, * keywordList;
	QLineEdit* inputField, *similarityLineEdit;
	QPushButton *showSimilarity;
public:
	GUI(QWidget* parent = Q_NULLPTR);
	~GUI() = default;
	void populateList();
public slots:
	void onChangeText();
	void similarity();
};


