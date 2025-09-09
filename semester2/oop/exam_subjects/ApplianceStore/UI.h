#pragma once
#include "Service.h"
class UI
{
private:
	Service service;
public:
	void run();
	void add();
	void showAll();
	void showInefficient();
	void saveToFile();
	void menu();
};

