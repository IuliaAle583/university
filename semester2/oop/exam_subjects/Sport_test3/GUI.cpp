#include "GUI.h"
#include <QHBoxLayout>
#include <QMessageBox>

GUI::GUI(Service& service) : service(service) {
    initGUI();
    loadAllSorted();
    connectSignals();
}

void GUI::initGUI() {
    list = new QListWidget;
    intensityLine = new QLineEdit;
    descLine = new QLineEdit;
    hourLine = new QLineEdit;
    filterButton = new QPushButton("Filter by Intensity");
    searchButton = new QPushButton("Search by Description + Start");

    auto* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("All Workouts (sorted):"));
    mainLayout->addWidget(list);

    auto* filterLayout = new QHBoxLayout;
    filterLayout->addWidget(new QLabel("Intensity >"));
    filterLayout->addWidget(intensityLine);
    filterLayout->addWidget(filterButton);
    mainLayout->addLayout(filterLayout);

    auto* searchLayout = new QHBoxLayout;
    searchLayout->addWidget(new QLabel("Description:"));
    searchLayout->addWidget(descLine);
    searchLayout->addWidget(new QLabel("Start Hour:"));
    searchLayout->addWidget(hourLine);
    searchLayout->addWidget(searchButton);
    mainLayout->addLayout(searchLayout);

    searchList = new QListWidget;
    totalLabel = new QLabel("Total duration: ");

    mainLayout->addWidget(new QLabel("Filtered Results:"));
    mainLayout->addWidget(searchList);
    mainLayout->addWidget(totalLabel);

    setLayout(mainLayout);
}

void GUI::loadAllSorted() {
    list->clear();
    auto workouts = service.getAllSortedByStartHour();
    for (const auto& w : workouts) {
        list->addItem(QString::fromStdString(
            to_string(w.getStartHour()) + "-" + to_string(w.getEndHour()) + " | " +
            w.getType() + " | Intensity: " + to_string(w.getIntensity()) + " | " + w.getDescription()
        ));
    }
}

void GUI::connectSignals() {
    QObject::connect(filterButton, &QPushButton::clicked, [&]() {
        bool ok;
        int threshold = intensityLine->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Error", "Invalid intensity");
            return;
        }

        list->clear();
        auto filtered = service.filterByIntensity(threshold);
        for (const auto& w : filtered) {
            list->addItem(QString::fromStdString(
                to_string(w.getStartHour()) + "-" + to_string(w.getEndHour()) + " | " +
                w.getType() + " | Intensity: " + to_string(w.getIntensity()) + " | " + w.getDescription()
            ));
        }
        });

    QObject::connect(searchButton, &QPushButton::clicked, [&]() {
        string desc = descLine->text().toStdString();
        bool ok;
        int hour = hourLine->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Error", "Invalid hour");
            return;
        }

        auto found = service.searchByDescriptionAndStartHour(desc, hour);
        searchList->clear();

        if (found.empty()) {
            QMessageBox::information(this, "No Results", "No matching workouts found.");
            totalLabel->setText("Total duration: 0");
            return;
        }

        for (const auto& w : found) {
            searchList->addItem(QString::fromStdString(
                to_string(w.getStartHour()) + "-" + to_string(w.getEndHour()) + " | " +
                w.getType() + " | Intensity: " + to_string(w.getIntensity()) + " | " + w.getDescription()
            ));
        }

        int total = service.getTotalDurationOf(found);
        totalLabel->setText("Total duration: " + QString::number(total));
        });
}