#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Driver {
private:
	string name;
	int latitude, longitude, score;
public:
	Driver() {
		this->name = " ";
		this->latitude = 0;
		this->longitude = 0;
		this->score = 0;
	}
	Driver(string name, int lat, int lon, int score) :
		name(name), latitude(lat), longitude(lon), score(score) {};
	~Driver() = default;
	string getName() { return this->name; };
	int getLongitude() { return this->longitude; };
	int getLatitude() { return this->latitude; };
	int getScore() { return this->score; };
	void increaseScore() { this->score++; };
};

class Report {
private:
	string description, reporter;
	int latitude, longitude;
	bool status;
public:
	Report(string d, string r, int lat, int lon, bool s) :
		description(d), reporter(r), latitude(lat), longitude(lon), status(s) {};
	~Report() = default;
	int getLatitude() { return this->latitude; };
	int getLongitude() { return this->longitude; };
	bool getStatus() { return this->status; };
	string getDescription() { return this->description; };
	string getReporter() { return this->reporter; };
	void setStatus(bool s) { this->status = s; };
};

