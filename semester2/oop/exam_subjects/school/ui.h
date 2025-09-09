#pragma once
//#include <iostream>
#include "service.h"

class UI {
private:
	Service service;
public:
	//UI() = default;
	explicit UI(Service& service) : service(service) {}
	void printMenu() const;
	void run();
	void addBill();
	void showAllBills();
	void showPaidBills();

};