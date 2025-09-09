
#pragma once
#include "QWidget"
#include "QLineEdit"
#include "QListWidget"
#include "QPushButton"
#include "QLabel"
#include "Service.h"
#include "QCheckBox"
#include "QSlider"

class GUI : public QWidget {

private:
    Service& service;
    QListWidget* weatherListWidget;
    QSlider* precipitationSlider;
    QPushButton* restoreButton;
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    QCheckBox* foggyBox, * sunnyBox, * rainBox, * thunderBox, * overcastBox;
    void filterByPrecipitation();
    void displayAll();
    void filterByCheckBoxes();
    void filter();

public:
    GUI(Service& service);
    ~GUI();
    void populateList(vector<weather> elements);
    void init_GUI();

};

