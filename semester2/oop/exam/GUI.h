#pragma once
#include "Model.h"
#include "Service.h"
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

class GUI:public QWidget
{
	Q_OBJECT
private:
    Service& service;
    Biologist biologist;
	QTableView* table;
	QSortFilterProxyModel* proxyModel;
    QListWidget* diseaseList;
    Model* model;

    QComboBox* speciesComboBox;
    QLineEdit* diseaseEdit;
    QPushButton* addDiseaseButton;

    QLineEdit* nameEdit, * speciesEdit, * sizeEdit, * diseasesEdit;
    QPushButton* addBacteriumButton;
    QPushButton* viewButton;

    void initGUI();
    void loadSpeciesComboBox();
    void connectSignalsAndSlots();
    void updateBacteria();
    void updateDiseases();
    void AddDiseaseClicked();
    void AddBacteriumClicked();
    void ViewButtonClicked();
public:
    GUI(Service& service, const Biologist& b, Model* originalModel, QWidget* parent = nullptr) :
        QWidget(parent), service(service), biologist(b), model(originalModel) {
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(originalModel);
        proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxyModel->setFilterKeyColumn(1);
        initGUI();
        loadSpeciesComboBox();
        connectSignalsAndSlots();
        updateBacteria(); 
    }
};

