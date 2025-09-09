#pragma once
#include "Astronomer.h"
#include <fstream>
#include <sstream>
#include <vector>

class Repository
{
private:
	vector<Astronomer> astronomers;
	vector<Star> stars;
public:
	void loadAstronomers();
	void loadStars();
	void saveStars();
	Repository() {
		loadAstronomers();
		loadStars();
	}
	~Repository() {
		saveStars();
	}
	vector<Astronomer>& getAstronomers() { return astronomers; };
	vector<Star>& getStars() { return stars; };
	void addStar(const Star& s) {
		stars.emplace_back(s);
	}
};

