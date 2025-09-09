#include "sport3.h"
#include <QtWidgets/QApplication>
#include "GUI.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    repo.loadFromFile("../sport.txt");

    Service service(repo);
    GUI gui(service);
    gui.show();
    return a.exec();
}
