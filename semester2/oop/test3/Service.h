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
	double computeKeywordSimilarity(Domain& doc, const string& smthing);
};



