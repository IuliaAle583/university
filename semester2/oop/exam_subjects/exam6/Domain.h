#pragma once
#include <iostream>
#include <string>
using namespace std;
class Reasercher
{
private:
	string name, position;
public:
	Reasercher(const string& name, const string& position):
		name(name),position(position){}
	string getName() const { return name; }
	string getPosition() const { return position; }

};

class Idea {
private:
	string title, description, status, creator;
	int duration;
public:
	Idea(const string& t, const string& d, const string& st, const string& cre, int dur):
		title(t),description(d),status(st),creator(cre),duration(dur){}
	string getTitle() const { return title; }
	string getDescription() const { return description; }
	string getStatus() const { return status; }
	string getCreator() const { return creator; }
	int getDuration() const { return duration; }
	void setStatus(const string& newStatus) {
		this->status = newStatus;
	}
	void setDescription(const string& newDes) {
		this->description = newDes;
	}
};

