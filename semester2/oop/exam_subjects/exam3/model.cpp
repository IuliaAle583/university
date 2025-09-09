#include "model.h"

int Model::rowCount(const QModelIndex& parent) const
{
    return this->repo.getStars().size();
}

int Model::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();
    Star star = this->repo.getStars()[row];
    if (role == Qt::DisplayRole) {
        switch (column) {
        case 0:
            return QString::fromStdString(star.getName());
        case 1:
            return QString::fromStdString(star.getConstellation());
        case 2:
            return QString::fromStdString(to_string(star.getRA()));
        case 3:
            return QString::fromStdString(to_string(star.getDEC()));
        case 4:
            return QString::fromStdString(to_string(star.getDiameter()));
        }
    }
    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return "Name of the star";
        case 1:
            return "Constellation";
        case 2:
            return "RA";
        case 3:
            return "Dec";
        case 4:
            return "Diameter";
        }
    }
    return QVariant();
}

void Model::updateData()
{
    beginResetModel();
    endResetModel();
    emit this->dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}
