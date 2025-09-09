#include "bills.h"
#include <QtWidgets/QApplication>
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //bills w;
    //w.show();
    GUI gui;
    gui.show();
    return QApplication::exec();
}
