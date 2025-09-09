#pragma once
#include "Person.h"
class UI
{
private:
	Person person;
public:
	void add();
	void getAll();
	void checkIfIll();
	void saveToFile();
	void menu();
	UI(const Person& p): person(p){}
	~UI() = default;
	void run();

};

