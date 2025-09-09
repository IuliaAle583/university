#pragma once
#include "Controller.h"

class UI
{
private:
	Controller controller;
public:
	UI() = default;
	~UI() = default;
	void run();
	void add();
	void showAll();
	void showAllEfficient();
	void writeToFile();
	void remove();
};

