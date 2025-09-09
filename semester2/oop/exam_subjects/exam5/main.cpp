#include <QApplication>
#include "Repository.h"
#include "Service.h"
#include "BiologistWindow.h"
#include <iostream>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Repository repo("biologists.txt", "bacteria.txt");
    Service service(repo);
    BacteriaModel* sharedModel = new BacteriaModel();
    sharedModel->setBacteria(service.getAllBacteria());
    for (const auto& b : service.getAllBiologists()) {
        auto* w = new BiologistWindow(service, b, sharedModel);
        w->show();
    }


    return app.exec();
}