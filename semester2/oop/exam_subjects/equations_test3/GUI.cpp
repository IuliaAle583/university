#include "GUI.h"

GUI::GUI(QWidget* parent) :QWidget(parent)
{
	this->setWindowTitle("Quadratic Equations");
	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->mainItems = new QListWidget;
	this->a = new QLineEdit;
	this->b = new QLineEdit;
	this->c = new QLineEdit;
	QLabel* labelA = new QLabel("a: ");
	QLabel* labelB = new QLabel("b: ");
	QLabel* labelC = new QLabel("c: ");
	this->add = new QPushButton("Add equation");
	this->computeSolution = new QPushButton("Compute solutions");
	this->solutionDisplay = new QLineEdit;
	this->solutionDisplay->setReadOnly(true);
	mainLayout->addWidget(mainItems);
	mainLayout->addWidget(labelA);
	mainLayout->addWidget(a);
	mainLayout->addWidget(labelB);
	mainLayout->addWidget(b);
	mainLayout->addWidget(labelC);
	mainLayout->addWidget(c);
	mainLayout->addWidget(add);
	mainLayout->addWidget(computeSolution);
	mainLayout->addWidget(solutionDisplay);
	this->setLayout(mainLayout);
	populateItems();
	QObject::connect(add, &QPushButton::clicked, this, &GUI::addEquation);
	QObject::connect(computeSolution, &QPushButton::clicked, this, &GUI::showSolution);
}

void GUI::populateItems()
{
	mainItems->clear();
	for (auto eq : service.getAllService()) {
		double a = eq.getA(), b = eq.getB(), c = eq.getC();
		QString text = QString::fromStdString(eq.toString());
		QListWidgetItem* item = new QListWidgetItem(text);
		if (eq.getDiscriminant() >= 0) {
			item->setBackground(Qt::green);
		}
		mainItems->addItem(item);
	}

}

void GUI::addEquation()
{
	try {
		double valA = std::stod(a->text().toStdString());
		double valB = std::stod(b->text().toStdString());
		double valC = std::stod(c->text().toStdString());
		Equations eq(valA, valB, valC);
		service.addEquation(eq);
		populateItems();
		a->clear();
		b->clear();
		c->clear();
	}
	catch (...) {
		QMessageBox::critical(this, "Error", "Invalid input");
	}
}

void GUI::showSolution()
{
	int index = mainItems->currentRow();
	if (index < 0) {
		QMessageBox::information(this, "Select", "Please select an equation");
		return;
	}
	Equations eq = service.getAllService()[index];
	QString result = QString::fromStdString(eq.solve());
	//QMessageBox::information( this,"Solutions", result);
	solutionDisplay->setText(result);
}
