
#pragma once
#include <QVBoxLayout>
#include <qwidget.h>
#include <qlistwidget.h>
#include "ShoppingBasket.h"
#include "service.h"
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QComboBox>
#include <QLabel.h>
#include <QDialog>


class UserModeGUI : public QDialog {

private:
    std::string size;
    int position;
    ShoppingBasket* ASB;
    Service& service;
    QListWidget* coatsListWidget;
    QListWidget* shoppingBasketListWidget;
    QComboBox* sizeComboBox;
    QPushButton* displayProductsButton, * openApplicationButton, * displayShoppingBasketButton;
    QPushButton* nextButton, * buyButton;
    


public:
    UserModeGUI(Service& service, ShoppingBasket* ASB, QWidget* parent = nullptr);
    ~UserModeGUI();
    void connectSignalsAndSlots();
    int getSelectedIndex();
    void initUserModeGUI();

    void connectSignalsAndSlotsDisplayFunction();

    void populateShoppingBag();

    void openApplication();

    void populateDisplayProducts(int position, std::vector<TrenchCoat> coats);
    void displayUserProducts();
    void nextProduct();
    void buyProduct();
    void initDisplayProducts();
    void displayProducts();
    void clearPopulatedList();

};
