#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//ART AUCTION
using namespace std;

class User {
private:
	string name;
	int id;
	string type;
public:
	User() { this->name = " "; this->id = 0; this->type = " "; }
	User(string name, int id, string type) : name(name), id(id), type(type) {};
	string getName() { return this->name; };
	string getType() { return this->type; };
	int getId() { return this->id; };
	~User() = default;
};

class Item {
private:
	string name;
	string category;
	int currentPrice;
	vector<tuple<int, string, int>> offers;
	//user id, date, offered sum is in tuple
public:
	Item() = default;
	Item(string name, string category, int price, vector<tuple<int, string, int>> offer = {}) :
		name(name), category(category), currentPrice(price), offers(offer) {};
	~Item() = default;
	string getName() { return this->name; };
	string getCategory() { return this->category; };
	int getPrice() { return this->currentPrice; };
	vector<tuple<int, string, int>> getOffers() {
		auto offer = offers;
		sort(offer.begin(), offer.end(),
			[](const tuple<int, string, int>& a, const tuple<int, string, int>& b) {
				return get<2>(a) < get<2>(b);
			});
		return offer;
	}
	void setPrice(int price) { this->currentPrice = price; };
	void addOffer(int id, string date, int price) {
		offers.emplace_back(make_tuple(id, date, price));
	}
	string toString()const {
		string result = name + ", " + category + ", " + to_string(currentPrice) + ", ";
		for (const auto& offer : offers) {
			result += to_string(get<0>(offer)) + " | " + get<1>(offer) + " | " + to_string(get<2>(offer)) + ", ";
		}
		return result;
	}
};
