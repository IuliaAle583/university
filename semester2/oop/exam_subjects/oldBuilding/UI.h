#pragma once
#include <iostream>
#include "Service.h"
using namespace std;
class UI
{
private:
	Service service;
public:
	void run();
	void addBuilding();
	void showAll();
	void showAllSorted();
	void saveToFile();
};

