#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "Service.h"
class GUI : public QWidget {
    Q_OBJECT
private:
    Service& service;

    QListWidget* allCarsList;
    QLineEdit* searchManufacturerEdit;
    QPushButton* searchButton;
    QListWidget* filteredCarsList;
    QLineEdit* countEdit;
public:
    GUI(Service& srv, QWidget* parent = nullptr) : service(srv) {
        initGUI();
        populateList();
        connectSignals();
    }
private:
    void initGUI();
    void populateList();
    void connectSignals();

};

