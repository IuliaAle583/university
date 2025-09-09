#include "GUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

GUI::GUI(Service& service, QWidget* parent) : QWidget(parent), service(service) {
    initGUI();
    connectSignals();
    loadTasks(taskList, service.getAllSorted(), true);
}

void GUI::initGUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    taskList = new QListWidget(this);
    layout->addWidget(taskList);

    QHBoxLayout* inputLayout = new QHBoxLayout;
    priorityBox = new QLineEdit(this);
    priorityBox->setPlaceholderText("Enter priority...");
    showButton = new QPushButton("Show tasks and duration", this);
    inputLayout->addWidget(priorityBox);
    inputLayout->addWidget(showButton);
    layout->addLayout(inputLayout);

    resultList = new QListWidget(this);
    layout->addWidget(resultList);

    totalLabel = new QLabel(this);
    layout->addWidget(totalLabel);

    errorLabel = new QLabel(this);
    layout->addWidget(errorLabel);

    setLayout(layout);
    setWindowTitle("Task Manager");
    resize(500, 600);
}

void GUI::connectSignals() {
    QObject::connect(showButton, &QPushButton::clicked, this, [this]() {
        string text = priorityBox->text().toStdString();
        try {
            int p = stoi(text);
            vector<Task> tasks = service.getByPriority(p);
            if (tasks.empty()) {
                errorLabel->setText("No tasks with this priority.");
                resultList->clear();
                totalLabel->setText("");
            }
            else {
                errorLabel->setText("");
                loadTasks(resultList, tasks);
                int total = service.getTotalDurationByPriority(p);
                totalLabel->setText(QString("Total duration: %1 minutes").arg(total));
            }
        }
        catch (...) {
            errorLabel->setText("Invalid input.");
        }
        });
}

void GUI::loadTasks(QListWidget* list, const vector<Task>& tasks, bool boldPriority1) {
    list->clear();
    for (const Task& t : tasks) {
        QString text = QString::fromStdString(t.getDescription()) +
            " | " + QString::number(t.getDuration()) +
            " min | Priority " + QString::number(t.getPriority());

        QListWidgetItem* item = new QListWidgetItem(text);
        if (boldPriority1 && t.getPriority() == 1) {
            QFont font = item->font();
            font.setBold(true);
            item->setFont(font);
        }
        list->addItem(item);
    }
}