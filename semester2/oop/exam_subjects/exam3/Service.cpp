#include "Service.h"

void Service::addStar(const string& name, const string& constel, const int& ra, const int& dec, const int& diam)
{
	Star star(name, constel, ra, dec, diam);
	if (name.empty() || dec <= 0) {
		throw exception();
	}
	repo.addStar(star);
}

vector<Star> Service::getFilteredStars(const string& name)
{
	vector<Star> starsFiltered;
	for (auto& star : repo.getStars()) {
		if (star.getName().find(name) != string::npos) {
			starsFiltered.emplace_back(star);
		}
	}
	return starsFiltered;
}

vector<Star> Service::getStarsInConstellation(const string& constellation)
{
	vector<Star> result;
	for (const auto& star : repo.getStars()) {
		if (star.getConstellation() == constellation)
			result.emplace_back(star);
	}
	return result;
}
