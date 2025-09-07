#include "Drawing.h"
#include <QPainter>

void Drawing::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font("Roboto", 14);
    painter.setFont(font);

    int y = 50;  
    int x = 20;

    for (const auto& species : biologist.getSpecies()) {
        painter.drawText(x, y, QString::fromStdString(species));

        int bx = x;          
        int by = y + 20;     

        auto bacteria = service.getBacteriaForSpecies(species);
        for (const auto& bact : bacteria) {
            painter.drawEllipse(bx, by, 40, 32);
            bx += 50;  
        }
        y += 80; 
    }
}


