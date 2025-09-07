#include "GUI.h"
#include "qformlayout.h"
#include "qgridlayout.h"
#include "CSVShoppingBasket.h"
#include "HTMLShoppingBasket.h"
#include "UserGUI.h"
#include "qlabel.h"
#include <iostream>
#include <QMessageBox>


void GUI::initGUI()
{

	QFont buttonsFont("Roboto", 13, true);
	this->saveButton = new QPushButton{ "Save File Type" };
	this->saveButton->setFont(buttonsFont);
	this->adminButton = new QPushButton{ "Admin Mode" };
	this->adminButton->setFont(buttonsFont);
	this->userButton = new QPushButton{ "User Mode" };
	this->userButton->setFont(buttonsFont);
	this->filetypeBox = new QComboBox{};
	this->filetypeBox->setFont(buttonsFont);
	this->filetypeBox->addItem("CSV file");
	this->filetypeBox->addItem("HTML file");
	this->filetypeBox->setStyleSheet(
		"QComboBox {"
		"   background-color: #4682B4;"    
		"   color: white;"                 
		"   border-radius: 5px;"           
		"   padding: 5px;"                 
		"}"
		"QComboBox QAbstractItemView {"
		"   background-color: #4682B4;"    
		"   color: white;"                 
		"}"
	);
	
	auto* mainLayout = new QVBoxLayout();
	auto* introduction = new QLabel();
	introduction->setText("WELCOME TO PROPER TRENCH COATS!");
	introduction->setAlignment(Qt::AlignCenter);
	QFont introduction_font("Roboto", 20);
	introduction->setFont(introduction_font);
	introduction_font.setWeight(QFont::Bold);  
	introduction->setFont(introduction_font);
	auto* space = new QLabel();
	space->setText("");
	auto* fileName = new QLabel;
	fileName->setText("Choose the type of the file");
	QFont font_file("Roboto", 15, true);
	fileName->setFont(font_file);
	mainLayout->addWidget(introduction);
	mainLayout->addWidget(space);
	mainLayout->addWidget(space);
	auto* fileDetails = new QFormLayout();
	fileDetails->addRow(fileName, this->filetypeBox);
	mainLayout->addLayout(fileDetails);
	auto* buttonsLayout = new QGridLayout();
	buttonsLayout->addWidget(this->saveButton, 0, 0);
	this->saveButton->setStyleSheet("background-color: #4682B4; color: white;");
	buttonsLayout->addWidget(this->userButton, 1, 0);
	this->userButton->setStyleSheet("background-color: #4682B4; color: white;");
	buttonsLayout->addWidget(this->adminButton, 2, 0);
	this->adminButton->setStyleSheet("background-color: #4682B4; color: white;");
	mainLayout->addLayout(buttonsLayout);
	auto* mainWindow = new QWidget();
	mainWindow->setLayout(mainLayout);
	mainWindow->setStyleSheet("background-color: #F0F8FF;");
	setCentralWidget(mainWindow);
}

GUI::GUI(Service& s, QWidget* p) : service(s), QMainWindow(p)
{
	this->initGUI();
	this->signalsAndSlots();
}

GUI::~GUI()
{
}

void GUI::signalsAndSlots()
{
	QObject::connect(this->saveButton, &QPushButton::clicked, this, &GUI::saveFileType);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::UserModeGUI);
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::AdminModeGUI);;
}

void GUI::AdminModeGUI()
{
	if (type == "empty") {
		QMessageBox::critical(this, "Error", "You have to choose a type for the file first!");
		return;
	}
	else {
		this->setCursor(Qt::WaitCursor);
		auto* amg = new AdminGUI{ service };
		this->setCursor(Qt::ArrowCursor);
	}

}

void GUI::saveFileType()
{
	this->type = this->filetypeBox->currentText().toStdString();
	if (this->type == "CSV file")
		this->shBasket = new CSVShoppingBasket();
	else if (this->type == "HTML file")
		this->shBasket = new HTMLShoppingBasket();
}

void GUI::UserModeGUI()
{
	if (type == "empty") {
		QMessageBox::critical(this, "Error", "You have to choose a type for the file first!");
		return;
	}
	if (this->shBasket == nullptr) {
		QMessageBox::critical(this, "Error", "Shopping basket is not initialized!");
		return;
	}
	this->setCursor(Qt::WaitCursor);
	auto* umg = new ::UserModeGUI(service, this->shBasket);
	this->setCursor(Qt::ArrowCursor);
}
