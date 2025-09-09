#include "GUI.h"
#include <QTextEdit>

void GUI::initGUI()
{
	tableView = new QTableView;
	tableView->setModel(proxyModel);

	titleEdit = new QLineEdit;
	descriptionEdit = new QLineEdit;
	durationEdit = new QLineEdit;

	titleEdit->setPlaceholderText("title");
	descriptionEdit->setPlaceholderText("description");
	durationEdit->setPlaceholderText("duration(1-3)");

	addIdeaButton = new QPushButton("Add idea");
	reviseIdeaButton = new QPushButton("revise idea");
	developButton = new QPushButton("Develop accepted idea");
	saveAllButton = new QPushButton("Save all accepted ideas");

	QVBoxLayout* mainLayout = new QVBoxLayout;
	QHBoxLayout* formLayout = new QHBoxLayout;

	formLayout->addWidget(titleEdit);
	formLayout->addWidget(descriptionEdit);
	formLayout->addWidget(durationEdit);
	formLayout->addWidget(addIdeaButton);

	mainLayout->addWidget(new QLabel("Position: "+QString::fromStdString(researcher.getPosition())));
	mainLayout->addWidget(tableView);
	mainLayout->addLayout(formLayout);
	mainLayout->addWidget(reviseIdeaButton);
	mainLayout->addWidget(developButton);
	mainLayout->addWidget(saveAllButton);

	this->setLayout(mainLayout);

	if (researcher.getPosition() != "Senior Researcher") {
		reviseIdeaButton->hide();
		saveAllButton->hide();
	}
}

void GUI::connectSignals()
{
	connect(addIdeaButton, &QPushButton::clicked, this, &GUI::addIdea);
	connect(reviseIdeaButton, &QPushButton::clicked, this, &GUI::reviseIdea);
	connect(developButton, &QPushButton::clicked, this, &GUI::developIdeas);
	connect(saveAllButton, &QPushButton::clicked, this, &GUI::saveAllIdeas);
}

void GUI::addIdea()
{
	string title = titleEdit->text().toStdString();
	string desc = descriptionEdit->text().toStdString();
	int dur = durationEdit->text().toInt();

	if (title.empty() || dur < 1 || dur>3) {
		QMessageBox::warning(this, "Invalid input", "Title must not be empty and duration must be 1-3.");

	}
	Idea idea(title, desc, "proposed", researcher.getName(), dur);
	repo.addIdea(idea);
	//model->updateData();
	Model::notifyAllModels();


}

void GUI::reviseIdea()
{
	QModelIndex idx = tableView->currentIndex();
	if (!idx.isValid()) return;
	QModelIndex modelIndex = proxyModel->mapToSource(idx);

	std::string title = model->data(modelIndex.sibling(modelIndex.row(), 0), Qt::DisplayRole).toString().toStdString();
	if (repo.acceptIdea(title)) {
		//model->updateData();
		Model::notifyAllModels();

	}
}

void GUI::developIdeas()
{
	vector<Idea> ideas = repo.getAcceptedIdeasByResearcher(researcher.getName());
	if (ideas.empty()) return;
	for (const Idea& idea : ideas) {
		QWidget* ideaWind = new QWidget;
		ideaWind->setWindowTitle(QString::fromStdString(idea.getTitle()));
		QTextEdit* descEdit = new QTextEdit(QString::fromStdString(idea.getDescription()));
		QPushButton* saveBtn = new QPushButton("Save");

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget(new QLabel("Edit Description: "));
		layout->addWidget(descEdit);
		layout->addWidget(saveBtn);
		ideaWind->setLayout(layout);

		connect(saveBtn, &QPushButton::clicked, [=]() {
			string newDesc = descEdit->toPlainText().toStdString();
			repo.updateIdeaDescription(idea.getTitle(), newDesc);
			repo.saveIdeaToFile(idea.getTitle());
			ideaWind->close();
			//model->updateData();
			Model::notifyAllModels();
			});
		ideaWind->show();
	}
}

void GUI::saveAllIdeas()
{
	repo.saveIdeas();
	QMessageBox::information(this, "Saved", "Accepted ideas saved to file");
}
