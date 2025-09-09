#pragma once
#include "Repository.h"

class Service
{private:
	Repository& repo;
public:
	Service(Repository& repo) : repo(repo) {};
	vector<Astronomer>& getAstronomers() const { return repo.getAstronomers(); }
	vector<Star>& getStars() const { return repo.getStars(); }
	void addStar(const string& name, const string& constel, const int& ra, const int& dec, const int& diam);
	vector<Star> getFilteredStars(const string& name);
	vector<Star> getStarsInConstellation(const string& constellation);
};

