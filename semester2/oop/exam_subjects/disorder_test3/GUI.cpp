#include "GUI.h"
#include <QString>
#include <QFont>
#include <QMessageBox>

GUI::GUI(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* searchLabel = new QLabel("Search by category or name:");
    searchLineEdit = new QLineEdit();

    disorderList = new QListWidget();

    QLabel* disorderLabel = new QLabel("Enter disorder name:");
    disorderNameLineEdit = new QLineEdit();
    showSymptomsButton = new QPushButton("Show Symptoms");

    symptomsList = new QListWidget();

    layout->addWidget(searchLabel);
    layout->addWidget(searchLineEdit);
    layout->addWidget(disorderList);
    layout->addWidget(disorderLabel);
    layout->addWidget(disorderNameLineEdit);
    layout->addWidget(showSymptomsButton);
    layout->addWidget(symptomsList);

    setLayout(layout);

    populateDisorderList();

    connect(searchLineEdit, &QLineEdit::textChanged, this, &GUI::filterDisorders);
    connect(showSymptomsButton, &QPushButton::clicked, this, &GUI::showSymptoms);
}

void GUI::populateDisorderList() {
    disorderList->clear();
    for (const auto& disorder : service.getAllDisorders()) {
        QString text = QString::fromStdString(disorder.getCategory() + " - " + disorder.getName());
        disorderList->addItem(text);
    }
}

void GUI::filterDisorders() {
    QString searchText = searchLineEdit->text().toLower();
    disorderList->clear();

    for (const auto& disorder : service.getAllDisorders()) {
        QString category = QString::fromStdString(disorder.getCategory()).toLower();
        QString name = QString::fromStdString(disorder.getName()).toLower();

        if (category.contains(searchText) || name.contains(searchText)) {
            QString display = QString::fromStdString(disorder.getCategory() + " - " + disorder.getName());
            disorderList->addItem(display);
        }
    }
}

void GUI::showSymptoms() {
    symptomsList->clear();
    QString disorderName = disorderNameLineEdit->text();
    std::vector<std::string> symptoms = service.getAllSymptomsFromName(disorderName.toStdString());

    if (symptoms.empty()) {
        QMessageBox::warning(this, "Error", "Disorder not found or has no symptoms.");
        return;
    }

    for (const auto& symptom : symptoms) {
        symptomsList->addItem(QString::fromStdString(symptom));
    }
}
