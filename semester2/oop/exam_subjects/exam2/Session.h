#pragma once
#include "Repository.h"
#include "Subject.h"
#include <set>
class Session:public Subject
{
private:
	Repository& repo;
	vector<string> messages;
	set<pair<string, string>> validations;
public:
	Session(Repository& repo) :repo(repo) {};
	vector<Driver> getDrivers() { return repo.getDrivers(); };
	vector<Report> getReports() { return repo.getReports(); };
	vector<string> getMessage() { return messages; };
	void addMessage(string name, string message);
	void addReport(string des, string name, int lat, int log, bool score);
	vector<Report> getInterestReports(string name);
	void addValidation(string des, string validator);
};

