#pragma once
#include <iostream>
#include <string>
using namespace std;

class Astronomer
{
private:
	string name, constellation;
public:
	Astronomer(string name, string constellation):
		name(name), constellation(constellation){}
	~Astronomer() = default;
	string getName() const { return this->name; };
	string getConstellation() const { return this->constellation; };
};

class Star {
	string name, constellation;
	int ra, dec, diameter;
public:
	Star(string n, string c, int ra, int dec, int diam):
		name(n),constellation(c),ra(ra),dec(dec),diameter(diam){}
	string getName() const { return name; };
	string getConstellation() const { return constellation; };
	int getRA() const { return ra; };
	int getDEC() const { return dec; };
	int getDiameter() const { return diameter; };
	inline bool operator<(const Star& other) const {
		return this->constellation < other.constellation;
	}
};