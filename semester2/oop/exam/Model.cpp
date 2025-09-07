#include "Model.h"
#include <algorithm>

Qt::ItemFlags Model::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}


void Model::BacteriaBySpecies(const std::vector<Bacterium>& newData)
{
    
	beginResetModel();
	bacteria = newData;
	endResetModel();
	emit modelUpdated();
}

int Model::rowCount(const QModelIndex& parent) const
{
	return static_cast<int>(bacteria.size());
}

int Model::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    const auto& bact = bacteria.at(index.row());
    switch (index.column()) {
    case 0: return QString::fromStdString(bact.getName());
    case 1: return QString::fromStdString(bact.getSpecies());
    case 2: return bact.getSize();
    case 3: {
        QString diseases;
        for (const auto& d : bact.getDiseases()) {
            diseases += QString::fromStdString(d) + ", ";
        }
        if (!diseases.isEmpty()) diseases.chop(2);
        return diseases;
    }
    }
    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section) {
        case 0: return "Name";
        case 1: return "Species";
        case 2: return "Size";
        case 3: return "Diseases";
    }
    return QVariant();
}

bool Model::setData(const QModelIndex& index, const QVariant& value, int role)
{
    /*
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    int row = index.row();
    int col = index.column();
    if (row >= static_cast<int>(bacteria.size()))
        return false;

    Bacterium& b = bacteria[row];
    std::string newVal = value.toString().toStdString();

    switch (col) {
    case 0:
        b.setName(newVal);
        break;
    case 1:
        b.setSpecies(newVal);
        break;
    case 2:
        try {
            b.setSize(std::stoi(newVal));
        }
        catch (...) {
            return false; 
        }
        break;
    default:
        return false; 
    }

    emit dataChanged(index, index);
    emit modelUpdated();  
    return true;*/
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    int row = index.row();
    int col = index.column();
    if (row >= static_cast<int>(bacteria.size()))
        return false;

    Bacterium& b = bacteria[row];

    std::string oldName = b.getName(); 
    std::string newVal = value.toString().toStdString();

    switch (col) {
    case 0:
        b.setName(newVal);
        break;
    case 1:
        b.setSpecies(newVal);
        break;
    case 2:
        try {
            b.setSize(std::stoi(newVal));
        }
        catch (...) {
            return false;
        }
        break;
    default:
        return false;
    }

    service.updateBacteria(oldName, b.getSpecies(), b.getSize());

    emit dataChanged(index, index);
    emit modelUpdated();
    return true;

}


