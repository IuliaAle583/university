#include "GUI.h"

void GUI::initGUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* allCarsLabel = new QLabel("All Cars:");
    allCarsList = new QListWidget;

    mainLayout->addWidget(allCarsLabel);
    mainLayout->addWidget(allCarsList);

    QFormLayout* formLayout = new QFormLayout;
    searchManufacturerEdit = new QLineEdit;
    formLayout->addRow("Manufacturer:", searchManufacturerEdit);
    mainLayout->addLayout(formLayout);

    searchButton = new QPushButton("Show cars");
    mainLayout->addWidget(searchButton);

    filteredCarsList = new QListWidget;
    countEdit = new QLineEdit;
    countEdit->setReadOnly(true);

    mainLayout->addWidget(new QLabel("Filtered cars:"));
    mainLayout->addWidget(filteredCarsList);
    mainLayout->addWidget(new QLabel("Number of cars:"));
    mainLayout->addWidget(countEdit);
}

void GUI::populateList()
{
    allCarsList->clear();
    auto cars = service.getAllCars();

    for (const auto& car : cars) {
        auto* item = new QListWidgetItem(QString::fromStdString(car.getManufacturer() + " - " + car.getModel()));
        QColor color(QString::fromStdString(car.getColor()));
        item->setForeground(color);
        allCarsList->addItem(item);
    }
}

void GUI::connectSignals()
{
    QObject::connect(searchButton, &QPushButton::clicked, [&]() {
        QString manufacturer = searchManufacturerEdit->text();
        auto cars = service.getCarsByManufacturer(manufacturer.toStdString());

        filteredCarsList->clear();
        for (const auto& car : cars) {
            auto* item = new QListWidgetItem(QString::fromStdString(car.getModel()));
            filteredCarsList->addItem(item);
        }

        int count = service.countCarsByManufacturer(manufacturer.toStdString());
        countEdit->setText(QString::number(count));
        });
}
