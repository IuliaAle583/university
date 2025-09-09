#pragma once
#include "Client.h"
#include "Dwelling.h"
#include <vector>
#include <algorithm>
class RealEstateAgency
{
private:
	vector<Dwelling> dwellings;
	vector<Client*> clients;
public:
	RealEstateAgency() {
		this->init();
	}
	void init();
	Dwelling addDwelling(string type, double price, bool isProfitable);
	void removeClient(string name);
	vector<Client*> getInterestedClients(Dwelling d);
	void writeToFile(string filename);
	vector<Client*> getClients() { return this->clients; };
	vector<Dwelling> getDwellings() { return this->dwellings; };
	~RealEstateAgency() {
		for (auto c : clients)
			delete c;
	}
};

