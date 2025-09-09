
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "Service.h"

class GUI : public QWidget {
    Q_OBJECT

private:
    Service& service;

    QListWidget* taskList;
    QLineEdit* priorityBox;
    QPushButton* showButton;
    QListWidget* resultList;
    QLabel* totalLabel;
    QLabel* errorLabel;

    void initGUI();
    void connectSignals();
    void loadTasks(QListWidget* list, const vector<Task>& tasks, bool boldPriority1 = false);

public:
    GUI(Service& service, QWidget* parent = nullptr);
};
