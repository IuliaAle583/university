#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_tests.h"

class tests : public QMainWindow
{
    Q_OBJECT

public:
    tests(QWidget *parent = nullptr);
    ~tests();

private:
    Ui::testsClass ui;
};
