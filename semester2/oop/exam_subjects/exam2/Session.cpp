#include "Session.h"

void Session::addMessage(string name, string message)
{
	Driver driver = repo.getDriver(name);
	if (driver.getName() == "") {
		throw runtime_error("Driver does not exist");
	}
	if (message.empty()) {
		throw runtime_error("Message is empty");
	}
	messages.emplace_back("[" + name + "]:" + message);
	notify();
}

void Session::addReport(string des, string name, int lat, int log, bool score)
{
	Driver driver = repo.getDriver(name);
	if (driver.getName() == "") {
		throw runtime_error("Driver does not exist");
	}
	auto dist = sqrt(pow(driver.getLatitude() - lat, 2) + pow(driver.getLongitude() - log, 2));
	//euclidian distance!!!!!
	if (des.empty() || dist > 20) {
		throw runtime_error("Invalid report");
	}
	repo.addReport(Report(des, name, lat, log, score));
	notify(); //!!!!!!!!!!!!!!!!
}

vector<Report> Session::getInterestReports(string name)
{
	//region of 10 units on radius
	vector<Report> rep;
	Driver driver = repo.getDriver(name);
	for (auto x : repo.getReports()) {
		auto dist= sqrt(pow(driver.getLatitude() - x.getLatitude(), 2) + pow(driver.getLongitude() - x.getLongitude(), 2));
		if (dist < 10) {
			rep.emplace_back(x);
		}
	}
	return rep;
}

void Session::addValidation(string des, string validator)
{
	auto rep = repo.getReportByDescription(des);
	if (rep.getReporter() == validator) {
		throw runtime_error("Cannot validate own report");
	}
	validations.insert({ des,validator });
	int nrValidations = 0;
	for (auto x : validations) {
		if (x.first == des)
			nrValidations++;
	}
	if (nrValidations >= 2) {
		repo.setReportStatus(des, true);
		repo.increaseScore(rep.getReporter());
	}
	notify(); //!!!!!!!!!
}
