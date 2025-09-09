
#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "Service.h"
using namespace std;

class GUI : public QWidget {
    Q_OBJECT

private:
    Service& service;

    QListWidget* list;
    QLineEdit* intensityLine;
    QLineEdit* descLine;
    QLineEdit* hourLine;
    QPushButton* filterButton;
    QPushButton* searchButton;
    QListWidget* searchList;
    QLabel* totalLabel;

    void initGUI();
    void loadAllSorted();
    void connectSignals();

public:
    GUI(Service& service);
};