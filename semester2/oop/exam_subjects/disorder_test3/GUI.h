#pragma once

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "Service.h"

class GUI : public QWidget {
    Q_OBJECT

private:
    Service service;

    QListWidget* disorderList;
    QLineEdit* searchLineEdit;

    QLineEdit* disorderNameLineEdit;
    QPushButton* showSymptomsButton;
    QListWidget* symptomsList;

public:
    GUI(QWidget* parent = nullptr);

private slots:
    void populateDisorderList();
    void filterDisorders();
    void showSymptoms();
};
