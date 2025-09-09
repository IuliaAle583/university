#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_weather3.h"

class weather3 : public QMainWindow
{
    Q_OBJECT

public:
    weather3(QWidget *parent = nullptr);
    ~weather3();

private:
    Ui::weather3Class ui;
};
