#include "searchEngine3.h"
#include <QtWidgets/QApplication>
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //searchEngine3 w;
    GUI gui;
    gui.show();
    return a.exec();
}
