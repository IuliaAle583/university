#pragma once
#include <QWidget>
#include <vector>
#include "model.h"
using namespace std;

class ConstellationWindow:public QWidget
{
	Q_OBJECT
private:
	Star selectedStar;
	vector<Star> starsInConstellation;
public:
	ConstellationWindow(Star selectedStar, vector<Star> stars, QWidget* parent = nullptr);
protected:
	void paintEvent(QPaintEvent* event) override;	//asta e tot timpul la fel
};

