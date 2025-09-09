#pragma once
#include "Repository.h"

class Service
{
private:
	Repository repo;
public:
	Service() {};
	~Service() = default;
	vector<Equations> getAllService() { return repo.getAll(); };
	void addEquation(Equations eq) {
		return repo.addEquation(eq);
	}
};

