#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sport3.h"

class sport3 : public QMainWindow
{
    Q_OBJECT

public:
    sport3(QWidget *parent = nullptr);
    ~sport3();

private:
    Ui::sport3Class ui;
};
