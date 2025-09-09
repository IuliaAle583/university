#include "Service.h"

vector<Vegetables> Service::getAllVegetables() {
	vector<Vegetables> all = repository.getAllVegetables();
	sort(all.begin(), all.end());
	return all;
}

vector<string>  Service::getAllUniqueFamilies() {
	ofstream fout("test.txt");

	vector<Vegetables> all = repository.getAllVegetables();
	sort(all.begin(), all.end());
	vector<string> allfinal;

	for (int i = 0; i < all.size(); i++) {
		bool found = 0;
		for (int j = 0; j < allfinal.size(); j++)
			if (all[i].getFamily() == allfinal[j]) found = 1;

		if (!found) {
			allfinal.push_back(all[i].getFamily());
			fout << all[i].toString();
		}
	}
	return allfinal;
}

/**
 * Returns all vegetables belonging to the given family.
 *
 * @param family The family name to filter vegetables by.
 * @return A vector of Vegetables whose family matches exactly the given family string.
 *
 * Behavior:
 *  - Iterates through all vegetables retrieved from the repository.
 *  - Selects only those whose getFamily() equals the input family.
 *  - Returns an empty vector if none match.
 */
vector<Vegetables> Service::getAllVegetablesBelongingToFamily(string family) {
	vector<Vegetables> all = repository.getAllVegetables();
	vector<Vegetables> allfinal;

	for (auto x : all)
		if (x.getFamily() == family) allfinal.push_back(x);

	return allfinal;
}

Vegetables Service::getVegetableFromName(string name) {
	vector<Vegetables> all = repository.getAllVegetables();
	for (auto x : all)
		if (x.getName() == name) return x;
	return Vegetables("none", "none", "None");
}

/**
 * Retrieves all vegetables belonging to the given family and returns them sorted by their name in ascending order.
 *
 * @param family The family name to filter vegetables by.
 * @return A vector of Vegetables belonging to the specified family, sorted alphabetically by their name.
 *
 * Behavior:
 *  - Calls getAllVegetablesBelongingToFamily to get all vegetables from the given family.
 *  - Sorts the resulting vector using a lambda comparator that compares vegetable names.
 *  - Returns the sorted vector.
 */
vector<Vegetables> Service::getAllVegetablesBelongingToFamilySorted(string family) {
	vector<Vegetables> vegetables = getAllVegetablesBelongingToFamily(family);
	sort(vegetables.begin(), vegetables.end(), [](const Vegetables& a, const Vegetables& b) {
		return a.getName() < b.getName();
		});

	return vegetables;
}
