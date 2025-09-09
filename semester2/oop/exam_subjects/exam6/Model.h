#pragma once
#include <QAbstractTableModel>
#include "Repository.h"

class Model : public QAbstractTableModel
{
private:
	Repository& repo;
    static vector<Model*> allModels;
public:
    Model(Repository& repo) : repo(repo) {
        allModels.push_back(this);
    }
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void updateData();
    ~Model() {
        allModels.erase(remove(allModels.begin(), allModels.end(), this), allModels.end());
    }
    static void notifyAllModels() {
        for (Model* m : allModels) {
            m->updateData();
        }
    }
};

