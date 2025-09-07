#include "GUI.h"
#include <sstream>
#include <fstream>
#include "Drawing.h"

void GUI::initGUI()
{
    this->setWindowTitle(QString::fromStdString(biologist.getName()));

    speciesComboBox = new QComboBox;
    table= new QTableView;
    diseaseList = new QListWidget;

    diseaseEdit = new QLineEdit;
    addDiseaseButton = new QPushButton("Add Disease");

    nameEdit = new QLineEdit;
    speciesEdit = new QLineEdit;
    sizeEdit = new QLineEdit;
    diseasesEdit = new QLineEdit;
    addBacteriumButton = new QPushButton("Add Bacteria");
    viewButton = new QPushButton("View Drawing");

    table->setModel(proxyModel);
    table->sortByColumn(0, Qt::AscendingOrder);

    nameEdit->setPlaceholderText("enter name");
    speciesEdit->setPlaceholderText("species");
    sizeEdit->setPlaceholderText("size");
    diseasesEdit->setPlaceholderText("diseases");

    auto* mainLay = new QVBoxLayout(this);
    auto* dataLay = new QHBoxLayout;
    auto* disLay = new QHBoxLayout;
    auto* addLay = new QHBoxLayout;

    dataLay->addWidget(nameEdit);
    dataLay->addWidget(speciesEdit);
    dataLay->addWidget(sizeEdit);
    dataLay->addWidget(diseasesEdit);

    disLay->addWidget(diseaseEdit);
    disLay->addWidget(addDiseaseButton);

    addLay->addWidget(addBacteriumButton);
    addLay->addWidget(viewButton);

    mainLay->addWidget(speciesComboBox);
    mainLay->addWidget(table);
    mainLay->addWidget(new QLabel("Diseases:"));
    mainLay->addWidget(diseaseList);
    mainLay->addLayout(addLay);
    mainLay->addLayout(dataLay);
    mainLay->addLayout(disLay);
    table->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    table->setSortingEnabled(true);
}

void GUI::loadSpeciesComboBox()
{
    speciesComboBox->clear();
    for (const auto& specie : biologist.getSpecies()) {
        speciesComboBox->addItem(QString::fromStdString(specie));
    }
}

void GUI::connectSignalsAndSlots()
{
    connect(speciesComboBox, &QComboBox::currentTextChanged, this, [this]() {
        updateBacteria();
        });

    connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
        updateDiseases();
        });

    connect(addDiseaseButton, &QPushButton::clicked, this, &GUI::AddDiseaseClicked);
    connect(addBacteriumButton, &QPushButton::clicked, this, &GUI::AddBacteriumClicked);
    connect(viewButton, &QPushButton::clicked, this, &GUI::ViewButtonClicked);

    connect(model, &Model::modelUpdated, this, [this]() {
        updateDiseases();
        });
}

void GUI::updateBacteria()
{
    string filter = speciesComboBox->currentText().toStdString();
    proxyModel->setFilterFixedString(QString::fromStdString(filter));
}

void GUI::updateDiseases()
{
    diseaseList->clear();

    QModelIndex proxyIndex = table->currentIndex();
    if (!proxyIndex.isValid()) return;

    QModelIndex sourceIndex = proxyModel->mapToSource(proxyIndex);
    string name = model->data(model->index(sourceIndex.row(), 0)).toString().toStdString();

    for (const auto& b : service.getAllBacteria()) {
        if (b.getName() == name) {
            for (const auto& d : b.getDiseases()) {
                diseaseList->addItem(QString::fromStdString(d));
            }
            break;
        }
    }
}

void GUI::AddDiseaseClicked()
{
    QModelIndex proxyIndex = table->currentIndex();
    if (!proxyIndex.isValid()) return;

    QModelIndex sourceIndex = proxyModel->mapToSource(proxyIndex);
    QString bacteriumName = model->data(model->index(sourceIndex.row(), 0), Qt::DisplayRole).toString();

    string disease = diseaseEdit->text().toStdString();

    if (!disease.empty()) {
        service.addDisease(bacteriumName.toStdString(), disease);
        model->BacteriaBySpecies(service.getAllBacteria());
        updateBacteria();
        diseaseEdit->clear();
    }
}

void GUI::AddBacteriumClicked()
{
    string name = nameEdit->text().toStdString();
    string species = speciesEdit->text().toStdString();
    int size = sizeEdit->text().toInt();
    string dText = diseasesEdit->text().toStdString();
    vector<string> diseases;

    stringstream iss(dText);
    string token;
    while (getline(iss, token, ',')) {
        diseases.push_back(token);
    }

    if (!service.addBacteria(name, species, size, diseases)) {
        QMessageBox::warning(this, "Error", "Name or species already exists.");
    }

    model->BacteriaBySpecies(service.getAllBacteria());

    nameEdit->clear();
    speciesEdit->clear();
    sizeEdit->clear();
    diseasesEdit->clear();

    updateBacteria();
    loadSpeciesComboBox();
}

void GUI::ViewButtonClicked()
{
    auto* drawing = new Drawing(service, biologist);
    drawing->show();
}
