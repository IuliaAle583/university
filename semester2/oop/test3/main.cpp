#include "test3.h"
#include <QtWidgets/QApplication>
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //test3 w;
    //w.show();
    GUI gui;
    gui.show();
    return a.exec();
}
