#include "ConstellationWindow.h"
#include <QPainter>
#include <algorithm>

ConstellationWindow::ConstellationWindow(Star selectedStar, vector<Star> stars, QWidget* parent):
	QWidget(parent),selectedStar(selectedStar),starsInConstellation(std::move(stars))
{
	this->setWindowTitle(QString::fromStdString("Constellation " + selectedStar.getConstellation()));
	this->resize(400, 400);
}

void ConstellationWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	//Creezi un obiect QPainter care este folosit pentru a desena pe widgetul curent (this)
	//this ii spune unde sa deseneze
	int w = width();
	int h = height();	//sunt dimensiunile ferestrei ca sa stiu unde sa desenez
	//valorile astea sunt granitele sa stiu cum sa imi impart desenul
	int minRA = min_element(starsInConstellation.begin(), starsInConstellation.end(),
		[](const Star& a, const Star& b) {return a.getRA() < b.getRA(); })->getRA();
	int maxRA=max_element(starsInConstellation.begin(), starsInConstellation.end(),
		[](const Star& a, const Star& b) {return a.getRA() < b.getRA(); })->getRA();
	int minDEC= min_element(starsInConstellation.begin(), starsInConstellation.end(),
		[](const Star& a, const Star& b) {return a.getDEC() < b.getDEC(); })->getDEC();
	int maxDEC = max_element(starsInConstellation.begin(), starsInConstellation.end(),
		[](const Star& a, const Star& b) {return a.getDEC() < b.getDEC(); })->getDEC();

	//now get the max range
	int raRange = maxRA - minRA;
	int decRange = maxDEC - minDEC;
	if (raRange == 0) raRange = 1;
	if (decRange == 0) decRange = 1;
	for (const auto& star : starsInConstellation) {
		//parcurg toate stelele si le desenez
		//normalize them sa incape in fereastra
		int x = int(((star.getRA() - minRA) / double(raRange)) * (w - 40)) + 20;
		int y = int((1 - (star.getDEC() - minDEC) / double(decRange)) * (h - 40)) + 20;

		//circle radius proportional to diameter
		int radius = max(3, star.getDiameter() / 10);
		if (star.getName() == selectedStar.getName())
		{
			painter.setBrush(Qt::red);
		}
		else {
			painter.setBrush(Qt::black);
		}
		painter.drawEllipse(QPointF(x, y), radius, radius); //partea care deseneaza in sine
		//QPointF(x, y) reprezintă poziția centrului cercului pe fereastră (în pixeli)
		//radius este raza cercului pe axa X (orizontală).
		//radius este raza cercului pe axa Y(verticală).
	}
}
