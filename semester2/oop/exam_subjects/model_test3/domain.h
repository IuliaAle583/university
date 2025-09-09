#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <vector>

class Bill {
public:
    //QString company;
    //QString serial;
    //double sum;
    //bool isPaid;
    //Bill() = default;
    //Bill(const QString& company, const QString& serial, double sum, bool paid) : company(company), serial(serial), sum(sum), isPaid(paid) {};
    ~Bill() = default;
    QString company;
    QString serial;
    double sum;
    bool isPaid;

    Bill() = default;
    Bill(const QString& c, const QString& s, double sum, bool paid)
        : company(c), serial(s), sum(sum), isPaid(paid) {}
};
