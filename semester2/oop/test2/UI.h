#pragma once
#include "Service.h"
class UI {
private:
	Service service;
public:
	void printMenu() const;
	void start();
	void add();
	void show();
	void saveFile();
};

