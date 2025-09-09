#pragma once
#include "Repository.h"
#include "subject.h"
#include <algorithm>

class Session :public Subject {
private:
	Repository& repo;
public:
	Session(Repository& repo) :repo(repo) {};
	vector<User> getUsers() { return repo.getUsers(); };
	vector<Item> getItems() { return repo.getItems(); };
	void addItem(string name, string category, int price);
	void setPrice(int index, int price);
};
