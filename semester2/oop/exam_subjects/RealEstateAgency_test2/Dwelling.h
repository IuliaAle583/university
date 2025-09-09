#pragma once
#include <string>
using namespace std;
class Dwelling
{
private:
	string type;
	double price;
	bool isProfitable;
public:
	Dwelling(string type , double price, bool prof) : type(type), price(price), isProfitable(prof) {};
	double normalBankRate();
	double largeBankRate();
	double getPrice() { return this->price; };
	bool Profitable() { return this->isProfitable; };
	~Dwelling() = default;
	string toString() {
		return "Dwelling\nTYpe " + type + "\nprice " + to_string(price) + "\nis profitable " + to_string(isProfitable) + "\n";
	}
};

