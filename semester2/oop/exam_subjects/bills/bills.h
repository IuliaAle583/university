#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_bills.h"

class bills : public QMainWindow
{
    Q_OBJECT

public:
    bills(QWidget *parent = nullptr);
    ~bills();

private:
    Ui::billsClass ui;
};
