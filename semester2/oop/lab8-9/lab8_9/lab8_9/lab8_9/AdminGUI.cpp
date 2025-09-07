#include "AdminGUI.h"
#include "qformlayout.h"
#include "qgridlayout.h"
#include <qlabel.h>
#include <QMessageBox>
#include <QGroupBox>
#include <QTableWidget>
#include "validator.h"

AdminGUI::AdminGUI(Service& service, QWidget* parent) : service{ service }, QDialog{ parent }
{
	this->initializeData();
	this->makeTable();
	this->signalsAndSlots();
}

AdminGUI::~AdminGUI()
{
}

void AdminGUI::signalsAndSlots()
{
    QObject::connect(this->displayButton, &QPushButton::clicked, this, &AdminGUI::goBack);
    QObject::connect(this->goBackButton, &QPushButton::clicked, this, &AdminGUI::clickGoBack);
    QObject::connect(this->coatsTable, &QTableWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getIndex();

        if (selectedIndex < 0)
            return;

        TrenchCoat coat = this->service.GetRepository()[selectedIndex];
        this->sizeBox->setCurrentText(QString::fromStdString(coat.GetSize()));
        this->colorEdit->setText(QString::fromStdString(coat.GetColor()));
        this->priceEdit->setText(QString::fromStdString(std::to_string(coat.GetPrice())));
        this->quantityEdit->setText(QString::fromStdString(std::to_string(coat.GetQuantity())));
        this->photographEdit->setText(QString::fromStdString(coat.GetPhotograph()));
        });

    QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addCoat);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteCoat);
    QObject::connect(this->updatePriceButton, &QPushButton::clicked, this, &AdminGUI::updatePriceCoat);
    QObject::connect(this->updateQuantityButton, &QPushButton::clicked, this, &AdminGUI::updateQuantityCoat);

}

int AdminGUI::getIndex() const
{
    QModelIndexList selectedIndexes = this->coatsTable->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        this->colorEdit->clear();
        this->priceEdit->clear();
        this->quantityEdit->clear();
        this->photographEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void AdminGUI::makeTable()
{
    this->coatsTable->clearContents();  
    this->coatsTable->setRowCount(0);   

    std::vector<TrenchCoat> coats = this->service.GetRepository();

    for (const TrenchCoat& coat : coats) {
        int row = this->coatsTable->rowCount();
        this->coatsTable->insertRow(row);  

        this->coatsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(coat.GetSize())));
        this->coatsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(coat.GetColor())));
        this->coatsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(coat.GetPrice()))));
        this->coatsTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(coat.GetQuantity()))));
        this->coatsTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(coat.GetPhotograph())));
    }
    this->coatsTable->setColumnWidth(0, 100);
}

void AdminGUI::addCoat()
{
    
    std::string size = this->sizeBox->currentText().toStdString();
    std::string color = this->colorEdit->text().toStdString();
    std::string price = this->priceEdit->text().toStdString();
    std::string quantity = this->quantityEdit->text().toStdString();
    std::string photograph = this->photographEdit->text().toStdString();

    int validate_price = Validator::validate_price_product(price);
    int validate_quantity = Validator::validate_quantity_product(quantity);


    if (!Validator::validate_color_product(color) || validate_price == -1
        || validate_quantity == -1 || !Validator::validate_photograph_product(photograph))
    {
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    }
    else
    {
        try {
            this->service.addService(size, color, stoi(price), stoi(quantity), photograph);
            QMessageBox::information(this, "Success", "Coat added successfully!");
        }
        catch (...)
        {
            QMessageBox::critical(this, "Error", "Couldn't add the product!");
            return;
        }
    }
    this->makeTable();

    size_t lastElement = this->service.GetRepository().size() - 1;
    this->coatsTable->selectRow(static_cast<int>(lastElement));
}

void AdminGUI::deleteCoat()
{
    std::string size = this->sizeBox->currentText().toStdString();
    std::string color = this->colorEdit->text().toStdString();
    std::string photograph = this->photographEdit->text().toStdString();
    if (!Validator::validate_color_product(color) || !Validator::validate_photograph_product(photograph))
    {
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    }
    else
    {
        try {
            this->service.deleteService(size, color, photograph, 1);
            QMessageBox::information(this, "Success", "Coat deleted successfully!");
        }
        catch (...)
        {
            QMessageBox::critical(this, "Error", "Couldn't delete the product!");
            return;
        }
    }
    this->makeTable();
    size_t lastElement = this->service.GetRepository().size() - 1;
    this->coatsTable->selectRow(static_cast<int>(lastElement));
}


void AdminGUI::updatePriceCoat()
{
    std::string size = this->sizeBox->currentText().toStdString();
    std::string color = this->colorEdit->text().toStdString();
    std::string photograph = this->photographEdit->text().toStdString();
    std::string price = this->priceEdit->text().toStdString();
    int validate_price = Validator::validate_price_product(price);

    if (!Validator::validate_color_product(color) || validate_price == -1
        || !Validator::validate_photograph_product(photograph))
    {
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    }
    else
    {
        try {
            this->service.updatePriceService(size, color, photograph, stoi(price));
            QMessageBox::information(this, "Success", "Price updated successfully!");
        }
        catch (...)
        {
            QMessageBox::critical(this, "Error", "Couldn't update the product!");
            return;
        }
    }
    this->makeTable();
    size_t lastElement = this->service.GetRepository().size() - 1;
    this->coatsTable->selectRow(static_cast<int>(lastElement));
}

void AdminGUI::updateQuantityCoat()
{
    std::string size = this->sizeBox->currentText().toStdString();
    std::string color = this->colorEdit->text().toStdString();
    std::string photograph = this->photographEdit->text().toStdString();
    std::string quantity = this->quantityEdit->text().toStdString();
    int validate_quantity = Validator::validate_quantity_product(quantity);
    if (!Validator::validate_color_product(color) || validate_quantity == -1 ||
        !Validator::validate_photograph_product(photograph))
    {
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    }
    else if (validate_quantity == 0) {
        try {
            this->service.deleteService(size, color, photograph, 1);
            QMessageBox::information(this, "Success", "Coat was sold out.\nDeleted successfully!");
        }
        catch (...) {
            QMessageBox::critical(this, "Error", "Couldn't delete the product!");
            return;
        }
    }
    else {
        try {
            this->service.updateQuantityService(size, color, photograph, stoi(quantity));;
            QMessageBox::information(this, "Success", "Quantity updated successfully!");
        }
        catch (...)
        {
            QMessageBox::critical(this, "Error", "Couldn't update the product!");
            return;
        }
    }
    this->makeTable();
    size_t lastElement = this->service.GetRepository().size() - 1;
    this->coatsTable->selectRow(static_cast<int>(lastElement));
}

void AdminGUI::initializeData()
{
    QFont buttonsFont("Consolas", 13, true);

    this->coatsTable = new QTableWidget{};
    this->coatsTable->setFont(buttonsFont);
    this->coatsTable->setColumnCount(5);
    this->coatsTable->setHorizontalHeaderLabels({ "Size", "Color", "Price", "Quantity", "Photograph" });
    this->coatsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);  

    this->coatsTable->setStyleSheet(
        "QTableWidget {"
        "   background-color: #ADD8E6;"
        "}"
        "QTableWidget::item:selected {"
        "   background-color: #ADD8E6;"
        "   color: black;"  
        "}"
    );
    this->coatsTable->setColumnWidth(4, 1000);
    
    this->goBackButton = new QPushButton{ "\u21A9" };
    this->goBackButton->setFont(QFont("Roboto", 30));
    //this->goBackButton->setFont(buttonsFont);
    this->goBackButton->setVisible(false);
    
    this->sizeBox = new QComboBox{};
    this->sizeBox->setFont(buttonsFont);

    this->sizeBox->addItem("XXS");
    this->sizeBox->addItem("XS");
    this->sizeBox->addItem("S");
    this->sizeBox->addItem("M");
    this->sizeBox->addItem("L");
    this->sizeBox->addItem("XL");
    this->sizeBox->addItem("XXL");

    this->colorEdit = new QLineEdit{};
    this->colorEdit->setFont(buttonsFont);

    this->priceEdit = new QLineEdit{};
    this->priceEdit->setFont(buttonsFont);

    this->quantityEdit = new QLineEdit{};
    this->quantityEdit->setFont(buttonsFont);

    this->photographEdit = new QLineEdit{};
    this->photographEdit->setFont(buttonsFont);

    this->addButton = new QPushButton{ "Add" };
    this->addButton->setFont(buttonsFont);

    this->deleteButton = new QPushButton{ "Delete" };
    this->deleteButton->setFont(buttonsFont);

    this->updatePriceButton = new QPushButton{ "Update Price" };
    this->updatePriceButton->setFont(buttonsFont);

    this->updateQuantityButton = new QPushButton{ "Update Quantity" };
    this->updateQuantityButton->setFont(buttonsFont);

    this->displayButton = new QPushButton{ "Display" };
    this->displayButton->setFont(buttonsFont);

    this->addButton->setStyleSheet("QPushButton { background-color: #ADD8E6; }");
    this->deleteButton->setStyleSheet("QPushButton { background-color: #ADD8E6; }");
    this->updatePriceButton->setStyleSheet("QPushButton { background-color: #ADD8E6; }");
    this->updateQuantityButton->setStyleSheet("QPushButton { background-color: #ADD8E6; }");
    this->displayButton->setStyleSheet("QPushButton { background-color: #ADD8E6; }");
    this->goBackButton->setStyleSheet("QPushButton { background-color: #ADD8E6; }");


    QLabel* space = new QLabel();
    space->setText("");

    QLabel* coatsText = new QLabel();
    coatsText->setText("The list of coats");
    QFont coatsFont("Consolas", 15, true);
    coatsText->setFont(coatsFont);

    auto* size = new QLabel();
    size->setText("Size");
    size->setFont(buttonsFont);

    auto* color = new QLabel();
    color->setText("Color");
    color->setFont(buttonsFont);

    auto* price = new QLabel();
    price->setText("Price");
    price->setFont(buttonsFont);

    auto* quantity = new QLabel();
    quantity->setText("Quantity");
    quantity->setFont(buttonsFont);

    auto* photograph = new QLabel();
    photograph->setText("Photograph");
    photograph->setFont(buttonsFont);

    QGroupBox* detailsGroup = new QGroupBox("Coat Details");
    QFormLayout* coatDetails = new QFormLayout();
    coatDetails->addRow(size, this->sizeBox);
    coatDetails->addRow(color, this->colorEdit);
    coatDetails->addRow(price, this->priceEdit);
    coatDetails->addRow(quantity, this->quantityEdit);
    coatDetails->addRow(photograph, this->photographEdit);
    detailsGroup->setLayout(coatDetails);

    QHBoxLayout* topButtonsLayout = new QHBoxLayout();
    topButtonsLayout->addWidget(this->addButton);
    topButtonsLayout->addWidget(this->deleteButton);
    this->addButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->deleteButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    
    QHBoxLayout* bottomButtonsLayout = new QHBoxLayout();
    bottomButtonsLayout->addWidget(this->updatePriceButton);
    bottomButtonsLayout->addWidget(this->updateQuantityButton);
    bottomButtonsLayout->addWidget(this->displayButton);
    bottomButtonsLayout->addWidget(this->goBackButton);
    this->goBackButton->setVisible(false);
    this->updatePriceButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->updateQuantityButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->displayButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    

    QVBoxLayout* actionsGroup = new QVBoxLayout();
    actionsGroup->addLayout(topButtonsLayout);
    actionsGroup->addLayout(bottomButtonsLayout);

    /*QGroupBox* actionsGroup = new QGroupBox("Actions");
    QGridLayout* buttonsLayout = new QGridLayout();
    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->deleteButton, 0, 1);
    buttonsLayout->addWidget(this->updatePriceButton, 1, 0);
    buttonsLayout->addWidget(this->updateQuantityButton, 1, 1);
    buttonsLayout->addWidget(this->displayButton, 1, 2);
    buttonsLayout->addWidget(this->goBackButton, 2, 1);
    this->addButton->setMinimumHeight(50);       
    this->deleteButton->setMinimumHeight(50);
    this->addButton->setMinimumWidth(120);       
    this->deleteButton->setMinimumWidth(120);
    actionsGroup->setLayout(buttonsLayout);*/

    auto* adminLayout = new QVBoxLayout();
    adminLayout->addWidget(coatsText);
    adminLayout->addWidget(this->coatsTable);
    adminLayout->addWidget(detailsGroup);
    //adminLayout->addWidget(actionsGroup);
    adminLayout->addLayout(actionsGroup);

    QWidget* adminDisplayWindow = new QWidget();
    adminDisplayWindow->setLayout(adminLayout);
    adminDisplayWindow->show();
}

void AdminGUI::goBack()
{
    this->addButton->setVisible(false);
    this->deleteButton->setVisible(false);
    this->updatePriceButton->setVisible(false);
    this->updateQuantityButton->setVisible(false);
    this->displayButton->setVisible(false);

    this->goBackButton->setVisible(true);

    this->coatsTable->setRowCount(static_cast<int>(this->service.GetRepository().size()));
    this->coatsTable->resizeColumnsToContents();  
    this->coatsTable->resizeRowsToContents();
}

void AdminGUI::clickGoBack()
{
    this->addButton->setVisible(true);
    this->deleteButton->setVisible(true);
    this->updatePriceButton->setVisible(true);
    this->updateQuantityButton->setVisible(true);
    this->displayButton->setVisible(true);

    this->goBackButton->setVisible(false);

    this->coatsTable->resizeColumnsToContents();
    this->coatsTable->resizeRowsToContents();
}
