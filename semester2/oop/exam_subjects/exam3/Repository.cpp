#include "Repository.h"
#include <algorithm>

void Repository::loadAstronomers()
{
	ifstream fin(R"(D:\desktop2\teste_oop\exam3\astronomers.txt)");
	string name, constel;
	string line;
	while (getline(fin, line)) {
		istringstream iss(line);
		getline(iss, name, '|');
		getline(iss, constel);
		astronomers.emplace_back(Astronomer(name, constel));
	}
	fin.close();
}

void Repository::loadStars()
{
	ifstream fin(R"(D:\desktop2\teste_oop\exam3\stars.txt)");
	string name, constel, ra, dec, diam;
	string line;
	while (getline(fin, line)) {
		istringstream iss(line);
		getline(iss, name, '|');
		getline(iss, constel, '|');
		getline(iss, ra, '|');
		getline(iss, dec, '|');
		getline(iss, diam);
		stars.emplace_back(Star(name, constel, stoi(ra), stoi(dec), stoi(diam)));

	}
	fin.close();
}

void Repository::saveStars()
{
	ofstream fout(R"(D:\desktop2\teste_oop\exam3\stars.txt)");
	sort(stars.begin(), stars.end());
	for (auto& star : stars) {
		fout << star.getName() << '|' << star.getConstellation() << '|' << star.getRA() << '|' << star.getDEC() << '|' << star.getDiameter() << endl;

	}
	fout.close();
}

