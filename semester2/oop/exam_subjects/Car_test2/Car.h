#pragma once
#include "Engine.h"
class Car
{
private:
	string bodyStyle;
	Engine* engine;
public:
	Car(string bodystyle = "", Engine* engine = nullptr) : bodyStyle(bodyStyle), engine(engine) {};
	~Car() = default;
	double computePrice();
	void destroyEngine();
	string toString();
};

