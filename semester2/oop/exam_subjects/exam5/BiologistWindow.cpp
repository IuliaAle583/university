//
// Created by mariasiu alexandra on 14.06.2025.
//

#include "BiologistWindow.h"
#include <QMessageBox>
#include "SpeciesDrawingWindow.h"
#include <sstream>

// BiologistWindow.cpp
BiologistWindow::BiologistWindow(Service& service, const Biologist& b, BacteriaModel* sharedModel, QWidget* parent)
    : QWidget(parent), service(service), biologist(b), model(sharedModel)
{
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(sharedModel);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(1);
    initGUI();
    loadSpeciesCombo();
    connectSignals();
    reloadBacteria(); // va apela setBacteria() pe modelul partajat
    this->resize(800, 600);
}


void BiologistWindow::initGUI() {
    this->setWindowTitle(QString::fromStdString(biologist.getName()));

    speciesCombo = new QComboBox;
    tableView = new QTableView;
    diseaseList = new QListWidget;

    diseaseInput = new QLineEdit;
    addDiseaseBtn = new QPushButton("Add Disease");

    nameInput = new QLineEdit;
    speciesInput = new QLineEdit;
    sizeInput = new QLineEdit;
    diseasesInput = new QLineEdit;
    addBacteriumBtn = new QPushButton("Add Bacterium");
    viewBtn = new QPushButton("View Summary");

    //tableView->setModel(model);
    tableView->setModel(proxyModel);

    nameInput->setPlaceholderText("Name");
    speciesInput->setPlaceholderText("Species");
    sizeInput->setPlaceholderText("Size");
    diseasesInput->setPlaceholderText("Disease1,Disease2");

    auto* mainLayout = new QVBoxLayout(this);
    auto* formLayout = new QHBoxLayout;
    auto* diseaseLayout = new QHBoxLayout;
    auto* buttonLayout = new QHBoxLayout;

    formLayout->addWidget(nameInput);
    formLayout->addWidget(speciesInput);
    formLayout->addWidget(sizeInput);
    formLayout->addWidget(diseasesInput);

    diseaseLayout->addWidget(diseaseInput);
    diseaseLayout->addWidget(addDiseaseBtn);

    buttonLayout->addWidget(addBacteriumBtn);
    buttonLayout->addWidget(viewBtn);

    mainLayout->addWidget(speciesCombo);
    mainLayout->addWidget(tableView);
    mainLayout->addWidget(new QLabel("Diseases:"));
    mainLayout->addWidget(diseaseList);
    mainLayout->addLayout(diseaseLayout);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
}

void BiologistWindow::loadSpeciesCombo() {
    speciesCombo->clear();
    for (const auto& s : biologist.getSpecies()) {
        speciesCombo->addItem(QString::fromStdString(s));
    }
}

void BiologistWindow::connectSignals() {
    connect(speciesCombo, &QComboBox::currentTextChanged, this, [this]() {
        reloadBacteria();
        });

    connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
        reloadDiseases();
        });

    connect(addDiseaseBtn, &QPushButton::clicked, this, [this]() {
        QModelIndex proxyIndex = tableView->currentIndex();
        if (!proxyIndex.isValid()) return;

        QModelIndex sourceIndex = proxyModel->mapToSource(proxyIndex);
        QString bacteriumName = model->data(model->index(sourceIndex.row(), 0), Qt::DisplayRole).toString();

        std::string disease = diseaseInput->text().toStdString();

        if (!disease.empty()) {
            service.addDisease(bacteriumName.toStdString(), disease);
            model->setBacteria(service.getAllBacteria());
            reloadBacteria();
            diseaseInput->clear();
        }
        });


    connect(addBacteriumBtn, &QPushButton::clicked, this, [this]() {
        std::string name = nameInput->text().toStdString();
        std::string species = speciesInput->text().toStdString();
        int size = sizeInput->text().toInt();
        std::string dText = diseasesInput->text().toStdString();
        std::vector<std::string> diseases;

        std::stringstream ss(dText);
        std::string token;
        while (getline(ss, token, ',')) {
            diseases.push_back(token);
        }

        if (!service.addBacterium(name, species, size, diseases)) {
            QMessageBox::warning(this, "Error", "Duplicate name + species.");
        }

        model->setBacteria(service.getAllBacteria());

        nameInput->clear();
        speciesInput->clear();
        sizeInput->clear();
        diseasesInput->clear();

        reloadBacteria(); 
        });


    connect(viewBtn, &QPushButton::clicked, this, [this]() {
        auto* drawingWin = new SpeciesDrawingWindow(service, biologist);
        drawingWin->show();
        });
    connect(model, &BacteriaModel::modelUpdated, this, [this]() {
        reloadDiseases(); 
        });
}

void BiologistWindow::reloadBacteria() {
    std::string filter = speciesCombo->currentText().toStdString();
    proxyModel->setFilterFixedString(QString::fromStdString(filter));
}

void BiologistWindow::reloadDiseases() {
    diseaseList->clear();

    QModelIndex proxyIndex = tableView->currentIndex();
    if (!proxyIndex.isValid()) return;

    QModelIndex sourceIndex = proxyModel->mapToSource(proxyIndex);
    std::string name = model->data(model->index(sourceIndex.row(), 0)).toString().toStdString();

    for (const auto& b : service.getAllBacteria()) {
        if (b.getName() == name) {
            for (const auto& d : b.getDiseases()) {
                diseaseList->addItem(QString::fromStdString(d));
            }
            break;
        }
    }
}
