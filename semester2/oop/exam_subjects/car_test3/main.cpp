#include "car3.h"
#include "GUI.h"
#include <QtWidgets/QApplication>
#include "tests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //car3 w;
    //w.show();
    Service service;
    GUI gui{ service };
    test_countCarsByManufacturer();
    gui.show();
    return a.exec();
}
