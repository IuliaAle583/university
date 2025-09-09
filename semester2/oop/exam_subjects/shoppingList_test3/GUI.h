#pragma once

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushbutton>
#include <QLabel>
#include "service.h"

class GUI : public QWidget
{
 Q_OBJECT
private:
    Service service;
    QListWidget* listWidgetAllItems;
    QListWidget* listWidgetFilteredItems;
    QLabel* labelForSearchByCategoryOrName;
    QLabel* labelForSearchByCategory;
    QLineEdit* searchByCategoryOrName;
    QLineEdit* searchByCategoryLineEdit;
    QPushButton* searchByCategoryButton;
public:
    GUI(QWidget* parent = Q_NULLPTR);
    void populateListWidgetAllItems();
public slots:
    void populateListWidgetBasedOnSearch();
    void filterByCategory();
    void printSelectedItem();
};


