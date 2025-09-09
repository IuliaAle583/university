#pragma once
#include "domain.h"
#include <fstream>
#include <sstream>

class Repository {
private:
	vector<User> users;
	vector<Item> items;
public:
	Repository() { 
		loadUsers();
		loadItems();
	}
	void loadUsers();
	void loadItems();
	~Repository() {
		saveUsersToFile();
		saveItemsToFile();
	}
	void saveUsersToFile();
	void saveItemsToFile();
	vector<User> getUsers() { return this->users; };
	vector<Item> getItems() { return this->items; };
	void addItem(Item e) { items.emplace_back(e); };
	void setPrice(int index, int price) { items[index].setPrice(price); };
};