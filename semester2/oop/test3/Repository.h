#pragma once
#include "Domain.h"
#include <vector>
#include <string>

class Repository
{
private:
	vector<Domain> documents;
public:
	Repository() { load(); };
	void load();
	~Repository() = default;
	vector<Domain> getAll() {
		return this->documents;
	};
};



