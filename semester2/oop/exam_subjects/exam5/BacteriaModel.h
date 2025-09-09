//
// Created by mariasiu alexandra on 14.06.2025.
//

#ifndef BACTERIAMODEL_H
#define BACTERIAMODEL_H

#include <QAbstractTableModel>
#include "Service.h"

class BacteriaModel : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<Bacterium> bacteria;

public:
    explicit BacteriaModel(QObject* parent = nullptr);

    void setBacteria(const std::vector<Bacterium>& newData);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
signals:
    void modelUpdated();
};

#endif // BACTERIAMODEL_H
