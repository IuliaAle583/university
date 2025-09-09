#include <QtWidgets/QApplication>
#include "GUI.h"
#include "Repository.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Repository repo;  
    if (repo.getReaserchers().empty()) {
        qDebug() << "No researchers loaded!";
        return -1;
    }
    for (const auto& researcher : repo.getReaserchers()) {
        GUI* gui = new GUI(repo, researcher);
        gui->show();
    }

    return a.exec();
}
