#include "Person.h"

void Person::addAnalysis(MedicalAnalysis* a)
{
	analyses.push_back(a);
}

vector<string> Person::getAll() 
{
	
	vector<string> result;
	for (auto a : analyses) {
		result.push_back(a->toString());
	}
	return result;
}

vector<MedicalAnalysis*> Person::getAllByMonth(int month)
{
	vector<MedicalAnalysis*> result;
	for (auto a : analyses) {
		if (a->getMonth() == month) {
			result.push_back(a);
		}
	}
	return result;
}

bool Person::isIll(int month) const
{
	bool hasAnalysis = false;

	for (auto a : analyses) {
		if (a->getMonth() == month) {
			hasAnalysis = true;
			if (a->isResultOK()) {
				return false; 
			}
		}
	}

	return hasAnalysis;
}

vector<string> Person::getAnalysesBetweenDates(string date1, string date2)
{
	vector<string> result;
	for (auto a : analyses) {
		if (a->getDate() >= date1 && a->getDate() <= date2) {
			result.push_back(a->toString()+" "+ (a->isResultOK() ? "OK" : "NOT OK"));
		}
	}
	return result;
}

void Person::writeToFile(string fileName, string date1, string date2)
{
	ofstream fout(fileName);
	if (!fout.is_open()) {
		cerr << "could not open the file\n";
		return;
	}
	for (auto a : analyses) {
		if (a->getDate() >= date1 && a->getDate() <= date2) {
			fout<<a->toString()<<" "<< (a->isResultOK() ? "OK" : "NOT OK") << "\n";
		}
	}
	fout.close();
}

/*
Implementare cu RAII	aka shared_ptr

//in rest s-ar fi comportat fix la fel
#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include "MedicalAnalysis.h"

class Person {
private:
	string name;
	vector<shared_ptr<MedicalAnalysis>> analyses;
public:
	Person(const string& name) : name(name) {}

	void addAnalysis(shared_ptr<MedicalAnalysis> m) {
		analyses.push_back(m);
	}

	void showAll() const {
		for (const auto& a : analyses)
			cout << a->toString() << endl;
	}

	bool isIll(int currentMonth) const {
		for (const auto& a : analyses)
			if (a->getMonth() == currentMonth && !a->isResultOK())
				return true;
		return false;
	}

	void saveBetweenDates(const string& start, const string& end, const string& filename) const {
		ofstream out(filename);
		for (const auto& a : analyses)
			if (a->getDate() >= start && a->getDate() <= end)
				out << a->toString() << " " << (a->isResultOK() ? "OK" : "NOT OK") << endl;
		out.close();
	}
};

*/
