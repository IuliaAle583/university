#include "exam4.h"
#include <QtWidgets/QApplication>
#include "GUI.h"
#include "SearchWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    Session session(repo);
    std::vector<GUI*> windows;  //am nevoie de el ca sa tina ferestrele in viata, altfel s-ar inchide imediat
    for (auto& user : repo.getUsers()) {
        GUI* w = new GUI(session, user.getName());
        w->show();
        windows.push_back(w);
    }
    SearchWindow* searchWindow = new SearchWindow(session, "Search");
    searchWindow->show();
    return a.exec();
}
