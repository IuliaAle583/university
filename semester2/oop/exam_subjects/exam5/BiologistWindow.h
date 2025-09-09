//
// Created by mariasiu alexandra on 14.06.2025.
//

#ifndef BIOLOGISTWINDOW_H
#define BIOLOGISTWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QTableView>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSortFilterProxyModel>
#include "Service.h"
#include "BacteriaModel.h"

class BiologistWindow : public QWidget {
    Q_OBJECT

private:
    QSortFilterProxyModel* proxyModel;
    Service& service;
    Biologist biologist;
    BacteriaModel* model;

    QComboBox* speciesCombo;
    QTableView* tableView;
    QListWidget* diseaseList;

    QLineEdit* diseaseInput;
    QPushButton* addDiseaseBtn;

    QLineEdit* nameInput, * speciesInput, * sizeInput, * diseasesInput;
    QPushButton* addBacteriumBtn;
    QPushButton* viewBtn;

    void initGUI();
    void loadSpeciesCombo();
    void connectSignals();
    void reloadBacteria();
    void reloadDiseases();

public:
    BiologistWindow(Service& service, const Biologist& b, BacteriaModel* sharedModel, QWidget* parent = nullptr);
};

#endif // BIOLOGISTWINDOW_H