#pragma once
#include "service.h"
#include "validator.h"
#include "ShoppingBasket.h"
#include "service.h"

class UI
{
private:

    Service& service;
    ShoppingBasket* basket{};

public:

    UI() = default;

    ~UI() = default;

    void start();

    void run();

    void Admin();

    void User();

    void displayBasket();

    static void adminMenu();

    void updatePrice();

    void updateQuantity();

    void deteleProduct();

    int displayProducts();

    int filterSize(const std::string& size);

    //void soldOut();

    void displayProdUser();

    void displayProdAdmin();

    void add();

    UI(Service& service);

    void purchaseMessage();

    void addButton();
};
