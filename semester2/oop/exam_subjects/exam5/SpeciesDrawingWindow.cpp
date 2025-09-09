//
// Created by mariasiu alexandra on 14.06.2025.
//

#include "SpeciesDrawingWindow.h"
#include <QPainter>
#include <QFont>

SpeciesDrawingWindow::SpeciesDrawingWindow(Service& srv, const Biologist& bio, QWidget* parent)
    : QWidget(parent), service(srv), biologist(bio)
{
    setWindowTitle(QString::fromStdString("View - " + biologist.getName()));
    resize(600, 400);
}

void SpeciesDrawingWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font("Arial", 12);
    painter.setFont(font);

    int y = 30;
    for (const auto& species : biologist.getSpecies()) {
        painter.drawText(20, y, QString::fromStdString(species));

        int x = 150;
        auto bacteria = service.getBacteriaForSpecies(species);
        for (const auto& b : bacteria) {
            if (b.getSize() < 5) {
                painter.drawEllipse(x, y - 15, 30, 30);  // Circle
            }
            else {
                painter.drawRect(x, y - 15, 30, 30);     // Rectangle
            }
            x += 40;
        }

        y += 50;
    }
}