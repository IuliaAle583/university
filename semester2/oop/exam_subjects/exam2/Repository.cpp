#include "Repository.h"
#include <fstream>
#include <sstream>

void Repository::loadDrivers()
{
	ifstream file(R"(D:\desktop2\teste_oop\exam2\exam2\drivers.txt)");
	string name, lat, log, score;
	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		getline(iss, name, '|');
		getline(iss, lat, '|');
		getline(iss, log, '|');
		getline(iss, score);
		drivers.emplace_back(Driver(name, stoi(lat), stoi(log), stoi(score)));
	}
	file.close();
}

void Repository::loadReports()
{
	ifstream file(R"(D:\desktop2\teste_oop\exam2\exam2\reports.txt)");
	string des, rep, lat, log, status;
	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		getline(iss, des, '|');
		getline(iss, rep, '|');
		getline(iss, lat, '|');
		getline(iss, log, '|');
		getline(iss, status);
		reports.emplace_back(Report(des, rep, stoi(lat), stoi(log), stoi(status)));
	}
	file.close();
}

void Repository::saveReports()
{
	ofstream file(R"(D:\desktop2\teste_oop\exam2\exam2\reports.txt)");
	for (auto& r : reports) {
		file << r.getDescription() << "|" << r.getReporter() << "|" << r.getLatitude() << "|" << r.getLongitude() << "|" << r.getStatus() << "\n";
	}
	file.close();
}
