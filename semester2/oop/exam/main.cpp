#include "exam.h"
#include <QtWidgets/QApplication>
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //exam w;
    //w.show();
    Repository repo;
    Service service(repo);
    Model* originalModel = new Model(service);
    originalModel->BacteriaBySpecies(service.getAllBacteria());
    for (const auto& b : service.getAllBiologists()) {
        auto* gui = new GUI(service, b, originalModel);
        gui->show();
    }
    return a.exec();
}
