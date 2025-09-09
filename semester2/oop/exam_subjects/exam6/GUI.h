#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include "Model.h"
#include "Repository.h"

class GUI:public QWidget
{
	Q_OBJECT

private:
    Repository& repo;
    Reasercher researcher;
    Model* model;
    QSortFilterProxyModel* proxyModel;

    QTableView* tableView;
    QLineEdit* titleEdit;
    QLineEdit* descriptionEdit;
    QLineEdit* durationEdit;
    QPushButton* addIdeaButton;
    QPushButton* reviseIdeaButton;
    QPushButton* developButton;
    QPushButton* saveAllButton;
public:
    GUI(Repository& repo, const Reasercher& res, QWidget* parent = nullptr) :
        QWidget(parent), repo(repo), researcher(res) {
        model = new Model(repo);
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(model);
        proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
        proxyModel->sort(4, Qt::AscendingOrder);
        initGUI();
        connectSignals();
        setWindowTitle(QString::fromStdString(researcher.getName()));

    }
private:
    void initGUI();
    void connectSignals();
public:
    void addIdea();
    void reviseIdea();
    void developIdeas();
    void saveAllIdeas();
};

