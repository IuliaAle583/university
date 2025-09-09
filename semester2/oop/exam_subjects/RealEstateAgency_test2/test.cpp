#include "RealEstateAgency.h"
#include <cassert>
#include <iostream>
void testAdd() {
	RealEstateAgency agency;
	Dwelling dw = agency.addDwelling("House", 60000, true);
	assert(agency.getDwellings().size() == 2);
	assert(agency.getDwellings()[1].getPrice() == 60000);
	cout << "test dwelling ok\n";

}

void testInterested() {
	RealEstateAgency agency;
	Dwelling dw = agency.addDwelling("House", 60000, true);
	vector<Client*> interested;
	interested = agency.getInterestedClients(dw);
	assert(interested.size() >= 1);
	assert(interested[0]->totalIncome() >= 6);
	cout << "interested passed\n";
}

void testRemove() {
	RealEstateAgency agency;
	agency.removeClient("Ana");
	assert(agency.getClients().size() == 3);
	agency.removeClient("BCR");
	assert(agency.getClients().size() == 2);
	cout << "test remove passed\n";
}

void callAllTests() {
	testAdd();
	testInterested();
	testRemove();
}