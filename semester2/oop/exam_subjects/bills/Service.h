#pragma once
#include "Repository.h"
class Service
{
private:
	Repository repo;
public:
	vector<Bill> getAllService() { return this->repo.getAll(); };
	vector<Bill> getAllSorted();
	double billsByCompany(string name);
};

