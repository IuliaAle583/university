#pragma once
#include <QAbstractTableModel>
#include "Service.h"
class Model:public QAbstractTableModel
{
    Q_OBJECT

private:
    std::vector<Bacterium> bacteria;
    Service& service;
public:
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    explicit Model(Service& srv, QObject* parent = nullptr) : QAbstractTableModel(parent), service(srv) {}

    void BacteriaBySpecies(const std::vector<Bacterium>& newData);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
signals:
    void modelUpdated();
};

