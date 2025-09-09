#include "GUI.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    initGUI();
    connectSignals();
    populateFamilies();
}

void MainWindow::initGUI() {
    auto* mainLayout = new QVBoxLayout(this);

    auto* topLayout = new QHBoxLayout();
    familyList = new QListWidget();
    vegetableList = new QListWidget();
    topLayout->addWidget(familyList);
    topLayout->addWidget(vegetableList);

    auto* searchLayout = new QHBoxLayout();
    searchLineEdit = new QLineEdit();
    searchLineEdit->setPlaceholderText("Enter vegetable name...");
    searchButton = new QPushButton("Search");
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    partsLabel = new QLabel("Parts to consume: ");

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(partsLabel);
}

void MainWindow::connectSignals() {
    QObject::connect(familyList, &QListWidget::itemClicked, this, [=](QListWidgetItem* item) {
        vegetableList->clear();
        QString selectedFamily = item->text();
        //auto vegetables = service.getAllVegetablesBelongingToFamily(selectedFamily.toStdString());
        auto vegetables = service.getAllVegetablesBelongingToFamilySorted(selectedFamily.toStdString());
        for (const auto& veg : vegetables) {
            QString text = QString::fromStdString(veg.getName() + " - " + veg.getList());
            vegetableList->addItem(text);
        }
        });

    QObject::connect(searchButton, &QPushButton::clicked, this, [=]() {
        QString name = searchLineEdit->text();
        if (name.isEmpty()) return;

        Vegetables veg = service.getVegetableFromName(name.toStdString());
        if (veg.getName() == "none") {
            partsLabel->setText("Vegetable not found.");
            return;
        }

        for (int i = 0; i < familyList->count(); ++i) {
            QListWidgetItem* item = familyList->item(i);
            if (item->text().toStdString() == veg.getFamily()) {
                item->setSelected(true);
                familyList->setCurrentItem(item);
                item->setBackground(Qt::yellow);
            }
            else {
                item->setSelected(false);
                item->setBackground(Qt::white);
            }
        }

        partsLabel->setText(QString("Parts to consume: %1").arg(QString::fromStdString(veg.getList())));
        });
}

void MainWindow::populateFamilies() {
    auto families = service.getAllUniqueFamilies();
    for (const auto& family : families) {
        familyList->addItem(QString::fromStdString(family));
    }
}
