#pragma once
//din 2023-07-11
#include <iostream>
#include <string>
using namespace std;

class Handrail {
public:
	virtual double computePrice()=0;
	Handrail() = default;
	~Handrail() = default;
};

class MetalHandrail :public Handrail {
	double computePrice() override {
		return 2.0;
	}
};

class WoodHandrail :public Handrail {
	double computePrice() override {
		return 2.5;
	}
};

class HandrailWithVerticalElements:public Handrail {
private:
	int nrElements;
	Handrail* handrail;
public:
	HandrailWithVerticalElements(Handrail* b, int n) : handrail (b), nrElements(n) {}
	~HandrailWithVerticalElements() {
		delete handrail;
	}
	double computePrice() override{
		return handrail->computePrice() + 5.0 * nrElements;
	}

};

class Stair {
public:
	int noSteps; // nu imi merge mai jos nici daca il am private nici potected, so shit
	Stair(int n) : noSteps(n) {}
	virtual double getCoefficient() const = 0;
	virtual std::string getDescription() const = 0;
	virtual double getPrice() const {
		return getCoefficient() * noSteps;
	}
	virtual ~Stair() = default;
};

class WoodStair :public Stair {
public:
	WoodStair(int n) : Stair(n) {}
	double getCoefficient() const override {
		return 1.5;
	}
	std::string getDescription() const override {
		return "wood stair";
	}
};
class MetalStair :public Stair {
public:
	MetalStair(int n):Stair(n){}
	double getCoefficient() const override {
		return 2.0;
	}
	string getDescription() const override {
		return "metal stair";
	}
};

//de pe sageti trebuie sa imi dau seama ce tip de scheme mai adaug pe langa ce imi zice
//aici pt ca imi arata sagetile cu -1 inseaman ca trebuie sa pun cei 2 pointeri ;a stair si handrail
class StairWithHandrail :public Stair {
private:
	Stair* stair;
	Handrail* handrail;
	double handrailLinearMeters;
public:
	StairWithHandrail(Stair* s, Handrail* h, double m)
		: Stair(s->noSteps), stair(s), handrail(h), handrailLinearMeters(m) {}

	double getCoefficient() const override {
		return 1.0;
	}

	std::string getDescription() const override {
		return stair->getDescription();
	}

	double getPrice() const override {
		return stair->getPrice() + handrail->computePrice() * handrailLinearMeters;
	}

	~StairWithHandrail() {
		delete stair;
		delete handrail;
	}
};

int runStair();

