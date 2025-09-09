#include "GUI.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QItemSelectionModel>
#include <QPainter>
#include "ConstellationWindow.h"


GUI::GUI(Astronomer astr, Service& service, Model* model) :
	astronomer{ astr }, service(service)
{
	this->starsModel = model; //modelul initial cu datele brute
	this->model = new QSortFilterProxyModel(); //noul model - gol
	this->model->setSourceModel(this->starsModel); // seteaza modelul sursa (datele reale) pentru proxy aka copie
	this->setWindowTitle(QString::fromStdString(this->astronomer.getName()));
	this->setUp();
}

void GUI::showConstellations()
{
	if (constellations->isChecked()) {	//verifica daca checkbox-ul e bifat
		QString filter = QString::fromStdString(this->astronomer.getConstellation());
		this->model->setFilterKeyColumn(1); //coloana pe care aplic filtrul - cea cu constelatia
		//adica aia dupa care filtrez - ii zic sa verifice expresia pe coloana asta
		//ii spune sa verifice doar coloana asta - daca nu setez va cauta pe toate coloanele
		this->model->setFilterRegularExpression(QRegularExpression(filter, QRegularExpression::CaseInsensitiveOption));
		//regular expression dupa care filtrez
	}
	else {
		this->model->setFilterRegularExpression(QRegularExpression()); //fara filtru aka afiseaza tot
	}
}

void GUI::addStar()
{
	string name = this->nameEdit->text().toStdString();
	string constellation = this->astronomer.getConstellation();
	int ra = this->raEdit->text().toInt();
	int dec = this->decEdit->text().toInt();
	int diameter = this->diameterEdit->text().toInt();
	try {
		this->service.addStar(name, constellation, ra, dec, diameter);
		this->starsModel->updateData();	//!!!!!!!!!!!!! trebuie sa il chem pt a modifica datele si in cel original
		//nu schimb si in proxy pt ca automat daca mi se modifica tabelul mare se modifica si proxy - e doar de prezentare
	}
	catch (exception& e) {
		QMessageBox::critical(this, "error", "Invalid data");
	}
}

void GUI::populateList()
{
	//cu stelele de care am nevoie doar
	this->filteredStars->clear();
	for (auto& star : this->service.getFilteredStars(this->starNameFilter->text().toStdString()))
		this->filteredStars->addItem(QString::fromStdString(star.getName()));
}

void GUI::viewStar()
{
	auto selectionModel = table->selectionModel();	//tine minte elementele selectate dintr-un tabel view
	//table->selectionModel() este exact obiectul selectat
	if (!selectionModel->hasSelection()) {
		QMessageBox::information(this, "Information", "Select a star first");
		return;
	}
	QModelIndex proxyIndex = selectionModel->currentIndex();	//indexul unde este selectat elementul
	QModelIndex sourceIndex = model->mapToSource(proxyIndex);	//IL MAPEZ IN TABELA ORIGINALA- CUM AM IN MEMORIE
	Star selectedStar = starsModel->getStarAtIndex(sourceIndex.row());
	ConstellationWindow* w = new ConstellationWindow(selectedStar, service.getStarsInConstellation(selectedStar.getConstellation()));
	w->show();
}

void GUI::setUp()
{
	auto* infoLayout = new QHBoxLayout();
	auto* nameLabel = new QLabel(QString::fromStdString("Name: " + this->astronomer.getName()));
	auto* constellationLabel = new QLabel(QString::fromStdString("Constellation: " + this->astronomer.getConstellation()));
	constellations = new QCheckBox("Filter Constellations");
	infoLayout->addWidget(nameLabel);
	infoLayout->addWidget(constellationLabel);
	infoLayout->addWidget(constellations);

	auto* layout = new QVBoxLayout();
	table = new QTableView();	//!!
	this->table->setModel(this->model);	//!! PROXY MODEL

	layout->addLayout(infoLayout);
	layout->addWidget(table);

	auto* newStarLayout = new QHBoxLayout();
	auto* nameStarLabel = new QLabel("Name of star: ");
	nameEdit = new QLineEdit();
	auto* raLabel = new QLabel("Ra: ");
	raEdit = new QLineEdit();
	auto* decLabel = new QLabel("Dec: ");
	decEdit = new QLineEdit();
	auto* diamLabel = new QLabel("Diameter: ");
	diameterEdit = new QLineEdit();
	auto* addStarButton = new QPushButton("ADD STAR");

	newStarLayout->addWidget(nameStarLabel);
	newStarLayout->addWidget(nameEdit);
	newStarLayout->addWidget(raLabel);
	newStarLayout->addWidget(raEdit);
	newStarLayout->addWidget(decLabel);
	newStarLayout->addWidget(decEdit);
	newStarLayout->addWidget(diamLabel);
	newStarLayout->addWidget(diameterEdit);
	newStarLayout->addWidget(addStarButton);

	auto* filteredStarsLayout = new QVBoxLayout();
	auto* filteredStarsLabel = new QLabel("Filter stars");
	starNameFilter = new QLineEdit();
	filteredStars = new QListWidget();
	filteredStarsLayout->addWidget(filteredStarsLabel);
	filteredStarsLayout->addWidget(starNameFilter);
	filteredStarsLayout->addWidget(filteredStars);

	layout->addLayout(newStarLayout);
	layout->addLayout(filteredStarsLayout);
	QPushButton* viewButton = new QPushButton("View Selected Star");
	layout->addWidget(viewButton);


	this->setLayout(layout);

	QObject::connect(constellations, &QCheckBox::stateChanged, this, &GUI::showConstellations);
	QObject::connect(addStarButton, &QPushButton::clicked, this, &GUI::addStar);
	QObject::connect(starNameFilter, &QLineEdit::textChanged, this, &GUI::populateList);
	QObject::connect(viewButton, &QPushButton::clicked, this, &GUI::viewStar);

}
