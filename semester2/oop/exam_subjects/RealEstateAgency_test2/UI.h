#pragma once
#include "RealEstateAgency.h"
class UI
{
private:
	RealEstateAgency agency;
public:
	UI() = default;
	~UI() = default;
	void run();
	void remove();
	void add();
	void showAll();
	void saveToFile();
};

