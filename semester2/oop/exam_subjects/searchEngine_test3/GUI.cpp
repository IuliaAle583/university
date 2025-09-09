#include "GUI.h"
#include <QMessageBox>


GUI::GUI(QWidget* parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainItems = new QListWidget();
	QLabel* label = new QLabel("Input field");
	inputField = new QLineEdit();
	showBestMatch = new QPushButton("Show best matching");
	//QLabel* search = new QLabel("search disorder");
	//searchDocument = new QLineEdit();
	//showKeywords = new QPushButton("Show keywords");
	keywordList = new QListWidget();
	keywordList->setVisible(false);
	mainLayout->addWidget(mainItems);
	mainLayout->addWidget(label);
	mainLayout->addWidget(inputField);
	mainLayout->addWidget(showBestMatch);
	//mainLayout->addWidget(search);
	//mainLayout->addWidget(searchDocument);
	//mainLayout->addWidget(showKeywords);
	mainLayout->addWidget(keywordList);
	setLayout(mainLayout);
	populateList();
	connect(inputField, &QLineEdit::textChanged, this, &GUI::onChangeText);
	connect(showBestMatch, &QPushButton::clicked, this, &GUI::bestMatch);
	//connect(showKeywords, &QPushButton::clicked, this, &GUI::showDocuments);
}

void GUI::populateList()
{
	mainItems->clear();
	vector<Domain> documents = service.getAll();
	for (auto x : documents)
		mainItems->addItem(QString::fromStdString(x.toString()));
}
/*
void GUI::showDocuments()
{
	QString docName = searchDocument->text();
	string name = docName.toStdString();
	keywordList->clear();
	vector<Domain> documents = service.getAll();
	bool found = false;
	for (auto& doc : documents) {
		if (doc.getName() == name) {
			found = true;
			vector<string> keywords = doc.getKeywords();
			for (auto& kw : keywords) {
				keywordList->addItem(QString::fromStdString(kw));
			}
			keywordList->setVisible(true);
			break;
		}
	}
	if (!found) {
		QMessageBox::warning(this, "Error", "document not found");
	}
}*/

void GUI::bestMatch()
{
	QWidget* window = new QWidget();
	QVBoxLayout* layout = new QVBoxLayout();
	string smthing = inputField->text().toStdString();
	auto ans = service.bestMatch(smthing);

	QString matchingDocument =
		QString::fromStdString("Matching document: " + ans.toString());

	QLabel* label =
		new QLabel(smthing.size() == 0 ? QString("No matching document")
			: matchingDocument);

	layout->addWidget(label);
	window->setLayout(layout);

	window->show();
}

void GUI::onChangeText() {
	if (inputField->text().size() == 0) {
		populateList();
		return;
	}
	string smthing = inputField->text().toStdString();
	vector<Domain> documents = service.search(smthing);
	mainItems->clear();
	for (auto x : documents) {
		mainItems->addItem(QString::fromStdString(x.toString())); 
	}
}