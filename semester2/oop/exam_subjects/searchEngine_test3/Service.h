#pragma once
#include "Repository.h"
class Service
{
private:
	Repository repo;
public:
	Service() {};
	~Service() = default;
	vector<Domain> getAll();
	vector<Domain> search(string smthing);
	Domain bestMatch(string smthing);

};

