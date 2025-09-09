#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
class Repository
{
private:
	vector<Bill> bills;
public:
	Repository() { this->load(); };
	void load();
	vector<Bill> getAll() { return this->bills; };
};

