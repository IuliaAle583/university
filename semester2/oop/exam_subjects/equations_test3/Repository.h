#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Equations.h"

class Repository
{
private:
	vector<Equations> equations;
public:
	Repository() { this->load(); };
	void load();
	~Repository() = default;
	vector<Equations> getAll();
	void addEquation(Equations eq);
};

