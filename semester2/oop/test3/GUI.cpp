#include "GUI.h"
#include <QMessageBox>


GUI::GUI(QWidget* parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainItems = new QListWidget();
	QLabel* label = new QLabel("Search: ");
	inputField = new QLineEdit();
	showSimilarity = new QPushButton("Show Similarity");
	keywordList = new QListWidget();
	keywordList->setVisible(false);
	similarityLineEdit = new QLineEdit();
	similarityLineEdit->setReadOnly(true);
	mainLayout->addWidget(mainItems);
	mainLayout->addWidget(label);
	mainLayout->addWidget(inputField);
	mainLayout->addWidget(keywordList);
	mainLayout->addWidget(showSimilarity);
	mainLayout->addWidget(similarityLineEdit);
	setLayout(mainLayout);
	populateList();
	connect(inputField, &QLineEdit::textChanged, this, &GUI::onChangeText);
	connect(showSimilarity, &QPushButton::clicked, this, &GUI::similarity);
}

void GUI::populateList()
{
	mainItems->clear();
	vector<Domain> documents = service.getAll();
	for (auto x : documents)
		mainItems->addItem(QString::fromStdString(x.toString()));
}

void GUI::similarity()
{
	QListWidgetItem* selectedItem = mainItems->currentItem();
	if (!selectedItem) {
		similarityLineEdit->setText("No document selected.");
		return;
	}

	QString selectedText = selectedItem->text();
	string smthing = inputField->text().toStdString();

	vector<Domain> documents = service.getAll();
	for (auto& doc : documents) {
		if (QString::fromStdString(doc.toString()) == selectedText) {
			double sim = service.computeKeywordSimilarity(doc, smthing);
			similarityLineEdit->setText(QString::number(sim, 'f', 4));
			return;
		}
	}
	similarityLineEdit->setText("Document not found.");
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