#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Service.h"

class MainWindow : public QWidget {
    Q_OBJECT

private:
    Service service;

    QListWidget* familyList;
    QListWidget* vegetableList;
    QLineEdit* searchLineEdit;
    QLabel* partsLabel;
    QPushButton* searchButton;

    void initGUI();
    void connectSignals();
    void populateFamilies();

public:
    MainWindow(QWidget* parent = nullptr);
};
