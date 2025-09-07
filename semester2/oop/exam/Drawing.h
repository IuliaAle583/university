#pragma once
#include <QWidget>
#include <vector>
#include "Service.h"
#include "Domain.h"

class Drawing : public QWidget
{
    Q_OBJECT
private:
    Service& service;
    Biologist biologist;

public:
    Drawing(Service& service, const Biologist& bio, QWidget* parent = nullptr) : QWidget(parent), service(service), biologist(bio) {
        setWindowTitle(QString::fromStdString(biologist.getName()));
        resize(800, 600);
    }

protected:
    void paintEvent(QPaintEvent* event) override;
};

