#include "equations_test3.h"
#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //equations_test3 w;
   // w.show();
    GUI gui;
    gui.show();
    return a.exec();
}
