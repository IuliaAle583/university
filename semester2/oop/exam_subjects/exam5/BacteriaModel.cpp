//
// Created by mariasiu alexandra on 14.06.2025.
//

#include "BacteriaModel.h"

BacteriaModel::BacteriaModel(QObject* parent)
    : QAbstractTableModel(parent) {}

void BacteriaModel::setBacteria(const std::vector<Bacterium>& newData) {
    beginResetModel();
    bacteria = newData;
    endResetModel();
    emit modelUpdated();
}

int BacteriaModel::rowCount(const QModelIndex& /*parent*/) const {
    return static_cast<int>(bacteria.size());
}

int BacteriaModel::columnCount(const QModelIndex& /*parent*/) const {
    return 4; // name, species, size, diseases
}

QVariant BacteriaModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole)
        return {};

    const auto& b = bacteria.at(index.row());

    switch (index.column()) {
    case 0: return QString::fromStdString(b.getName());
    case 1: return QString::fromStdString(b.getSpecies());
    case 2: return b.getSize();
    case 3: {
        QString joined;
        for (const auto& d : b.getDiseases()) {
            joined += QString::fromStdString(d) + ", ";
        }
        if (!joined.isEmpty()) joined.chop(2); // remove trailing ", "
        return joined;
    }
    default: return {};
    }
}

QVariant BacteriaModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section) {
    case 0: return "Name";
    case 1: return "Species";
    case 2: return "Size";
    case 3: return "Diseases";
    default: return {};
    }
}