#include "exam3.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "model.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    auto* model = new Model(repo);  //creaza modelul pe baza repository-ului
    Service service(repo);
    for (const auto& astr : service.getAstronomers()) {
        auto* astrWindow = new GUI(astr, service, model);
        astrWindow->show();
    }
    return a.exec();
}
