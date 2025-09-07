#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab8_9.h"

class lab8_9 : public QMainWindow
{
    Q_OBJECT

public:
    lab8_9(QWidget *parent = nullptr);
    ~lab8_9();

private:
    Ui::lab8_9Class ui;
};
