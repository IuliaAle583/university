#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//2023-06-16
class IceCream {
public:
	virtual string getDescription() const = 0;
	virtual double computePrice() const = 0;
	virtual ~IceCream() = default;
};

class SimpleIceCream : public IceCream {
private:
	string description;
	double price;
public:
	SimpleIceCream(const string& desc, double p): description(desc),price(p){}
	string getDescription() const override {
		return "simple ice cream with " + description+"\n";
	}
	double computePrice() const override {
		return price;
	}

	
};

class IceCreamWithTopping : public IceCream {
protected:
	IceCream* icecream;	// de pe sageata imi dau seama
	//asta se numeste agregare
public:
	IceCreamWithTopping(IceCream* base) : icecream(base) {}
	virtual string addTopping() const = 0;
	string getDescription() const override {
		return icecream->getDescription() + " " + addTopping();
	}
	double computePrice() const override {
		return icecream->computePrice() + getToppingPrice();
	}
	virtual double getToppingPrice() const = 0;
	virtual ~IceCreamWithTopping() {
		delete icecream;
	}
};

// d) IcecreamWithChocolateTopping
class IcecreamWithChocolateTopping : public IceCreamWithTopping {
public:
	IcecreamWithChocolateTopping(IceCream* base) : IceCreamWithTopping(base) {}

	string addTopping() const override {
		return "with chocolate topping";
	}

	double getToppingPrice() const override {
		return 3.0;
	}
};

// IcecreamWithCaramelTopping
class IcecreamWithCaramelTopping : public IceCreamWithTopping {
public:
	IcecreamWithCaramelTopping(IceCream* base) : IceCreamWithTopping(base) {}

	string addTopping() const override {
		return "with caramel topping";
	}

	double getToppingPrice() const override {
		return 2.0;
	}
};

class Order {
private:
	vector<IceCream*> icecreams;
public:
	void addIcecream(IceCream* ic) {
		icecreams.push_back(ic);
	}

	void printOrder() const {
		// Copiem vectorul pointerilor pentru sortare fără a modifica ordinea originală
		vector<IceCream*> sortedIcecreams = icecreams;

		// Sortează descrescător după preț
		sort(sortedIcecreams.begin(), sortedIcecreams.end(),
			[](IceCream* a, IceCream* b) {
				return a->computePrice() > b->computePrice();
			});

		for (auto ic : sortedIcecreams) {
			cout << ic->getDescription() << " - " << ic->computePrice() << " RON\n";
		}
	}

	~Order() {
		for (auto ic : icecreams) {
			delete ic;
		}
	}
};

Order* createorder();

