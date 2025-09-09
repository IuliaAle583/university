#include "test3_model.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Service serv;
    serv.loadBillsFromFile(R"(D:\desktop2\teste_oop\test3_model\bills.txt)");
    test3_model w(&serv);
    w.show();
    return a.exec();
}
