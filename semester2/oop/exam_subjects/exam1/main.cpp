#include "exam1.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "session.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // exam1 w;
    //w.show();
    Repository repo;
    Session session(repo);
    for (auto& user : repo.getUsers()) {
        GUI* gui = new GUI(session, user.getId());
        gui->show();
    }
    return a.exec();
}
