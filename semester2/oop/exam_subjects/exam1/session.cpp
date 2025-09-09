#include "session.h"

void Session::addItem(string name, string category, int price)
{
	if (name.empty() || price < 1) {
		throw runtime_error("invalid item");
	}
	auto it = Item(name, category, price);
	repo.addItem(it);
	notify();	//notify of the change!!!!!!!
}

void Session::setPrice(int index, int price)
{
	repo.setPrice(index, price);
	notify();
}
