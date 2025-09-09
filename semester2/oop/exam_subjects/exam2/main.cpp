#include "exam2.h"
#include <QtWidgets/QApplication>
#include "GUI.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;

    Session session(repo);

    for (auto& x : repo.getDrivers()) {
        auto window = new Window(session, x);
        window->show();
    }
    return a.exec();
}
