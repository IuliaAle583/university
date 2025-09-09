#pragma once
#include <string>
using namespace std;

class Patient {
private:
	string name;
	int age;
	bool infected;
	int roomNumber;
public:
	Patient();
	Patient(string name, int age, bool infected, int roomNumber);

	void setName(const string& name);
	void setAge(int age);
	void setInfected(bool infected);
	void setRoom(int number);

	string getName();
	int getAge();
	bool getInfected();
	int getRoomNumber();

};
