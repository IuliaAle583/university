#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
class Person
{
private:
	string name;
	vector<MedicalAnalysis*> analyses;
public:
	Person(const string& name): name(name){}
	~Person() {
		for (auto a : analyses) {
			delete a;
		}

	}
	void addAnalysis(MedicalAnalysis* a);
	vector<string> getAll();
	vector<MedicalAnalysis*> getAllByMonth(int month);
	bool isIll(int month) const;
	vector<string> getAnalysesBetweenDates(string date1, string date2);
	void writeToFile(string fileName, string date1, string date2);
};

