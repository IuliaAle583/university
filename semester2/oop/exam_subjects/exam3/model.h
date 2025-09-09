#pragma once
#include "Repository.h"
#include <QAbstractTableModel>

class Model: public QAbstractTableModel
{
private:
	Repository& repo;
public:
	Model(Repository& repo) :repo(repo) {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	void updateData();
	Star getStarAtIndex(int index) {
		return repo.getStars()[index];
	}
};

