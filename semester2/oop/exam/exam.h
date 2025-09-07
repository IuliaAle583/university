#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_exam.h"

class exam : public QMainWindow
{
    Q_OBJECT

public:
    exam(QWidget *parent = nullptr);
    ~exam();

private:
    Ui::examClass ui;
};
