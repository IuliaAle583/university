#include "taskManager3.h"
#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    repo.loadFromFile("../tasks.txt");

    Service service(repo);
    GUI gui(service);
    gui.show();
    return a.exec();
}
