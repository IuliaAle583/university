#pragma once
#include "Domain.h"

class Repository
{
private:
	vector<Driver> drivers;
	vector<Report> reports;
public:
	vector<Driver> &getDrivers() { return this->drivers; };
	vector<Report> &getReports() { return this->reports; };
	Repository() {
		this->loadDrivers();
		this->loadReports();
	}
	void loadDrivers();
	void loadReports();
	//void saveDrivers();
	void saveReports();
	~Repository() { this->saveReports(); };
	Driver& getDriver(string name) {
		for (auto& d : drivers) {
			if (d.getName() == name)
				return d;
		}
		throw runtime_error("Driver not found");
	}
	Report& getReportByDescription(string description) {
		for (auto& r : reports) {
			if (r.getDescription() == description)
				return r;
		}
		throw runtime_error("Report not found");
	}
	void setReportStatus(string description, bool status) {
		getReportByDescription(description).setStatus(status);
	}
	void addReport(const Report& report) {
		reports.emplace_back(report);
	}
	void increaseScore(string name) {
		getDriver(name).increaseScore();
	}
};

