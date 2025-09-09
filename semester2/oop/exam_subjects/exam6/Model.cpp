#include "Model.h"

std::vector<Model*> Model::allModels;

int Model::rowCount(const QModelIndex& parent) const
{
	return repo.getIdeas().size();
}

int Model::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant Model::data(const QModelIndex& index, int role) const
{
	if(role!=Qt::DisplayRole)
		return QVariant();
	const Idea& idea = repo.getIdeas()[index.row()];
	switch (index.column()) {
	case 0: return QString::fromStdString(idea.getTitle());
	case 1: return QString::fromStdString(idea.getDescription());
	case 2: return QString::fromStdString(idea.getStatus());
	case 3: return QString::fromStdString(idea.getCreator());
	case 4: return idea.getDuration();
	}
	return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
		return QVariant();
	switch (section) {
	case 0: return "Title";
	case 1: return "Description";
	case 2: return "Status";
	case 3: return "Creator";
	case 4: return "Duration";
	}
	return QVariant();
}

void Model::updateData()
{
	beginResetModel();
	endResetModel();
	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}
