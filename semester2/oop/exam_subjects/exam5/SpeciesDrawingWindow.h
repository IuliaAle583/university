//
// Created by mariasiu alexandra on 14.06.2025.
//

#ifndef SPECIESDRAWINGWINDOW_H
#define SPECIESDRAWINGWINDOW_H

#include <QWidget>
#include <vector>
#include "Service.h"
#include "Domain.h"

class SpeciesDrawingWindow : public QWidget {
    Q_OBJECT

private:
    Service& service;
    Biologist biologist;

public:
    SpeciesDrawingWindow(Service& srv, const Biologist& bio, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif
