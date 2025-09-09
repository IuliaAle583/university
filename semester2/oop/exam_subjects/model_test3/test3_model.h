#pragma once

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <vector>
#include "ui_test3_model.h"
#include "service.h"

class test3_model : public QMainWindow
{
    Q_OBJECT

public:
    test3_model(Service* service, QWidget *parent = nullptr);
    ~test3_model();

private slots:
    void filterBills();
    void calculateTotal();
private:
    //Ui::test3_modelClass ui;
    void populateList(const std::vector<Bill>& bills);
    Service* service;
    QListWidget* listWidget;
    QCheckBox* filterCheckBox;
    QCheckBox* showPaid;
    QLineEdit* companyInput;
    QPushButton* calcButton;
    QLabel* resultLabel;
    
};
