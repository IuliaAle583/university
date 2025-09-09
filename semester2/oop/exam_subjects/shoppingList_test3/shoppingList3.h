#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_shoppingList3.h"

class shoppingList3 : public QMainWindow
{
    Q_OBJECT

public:
    shoppingList3(QWidget *parent = nullptr);
    ~shoppingList3();

private:
    Ui::shoppingList3Class ui;
};
