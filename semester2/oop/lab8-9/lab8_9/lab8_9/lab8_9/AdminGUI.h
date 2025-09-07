#pragma once
#include <QWidget>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTableWidget>
#include "service.h"
#include <QDialog>
class AdminGUI: public QDialog
{
private:
    Service& service;
    QTableWidget* coatsTable;
    QLineEdit* colorEdit, * priceEdit, * quantityEdit, * photographEdit;
    QComboBox* sizeBox;
    QPushButton* addButton, * deleteButton, * updatePriceButton, 
        * updateQuantityButton, * displayButton, *goBackButton;

public:
    AdminGUI(Service& service, QWidget* parent = NULL);
    ~AdminGUI();
    void signalsAndSlots();
    int getIndex() const;
    void makeTable();
    void addCoat();
    void deleteCoat();
    void updatePriceCoat();
    void updateQuantityCoat();
    void initializeData();
    void goBack();
    void clickGoBack();
};

