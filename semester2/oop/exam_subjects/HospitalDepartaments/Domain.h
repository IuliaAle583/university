#pragma once
#include <string>
using namespace std;
class HospitalDepartment
{
	protected:
		string hospitalName;
		int numberOfDoctors;
public:
	HospitalDepartment(string name, int nr) : hospitalName(name), numberOfDoctors(nr) {};
	virtual bool isEfficient() = 0;
	virtual string toString();
	~HospitalDepartment() = default;
	string getName() const { return hospitalName; }
};

class NeonatalUnit : public HospitalDepartment {
private:
	int numberOfMothers;
	int numberOfNewborns;
	double averageGrade;
public:
	NeonatalUnit(string name, int nr, int mother, int newborn, double grade) :HospitalDepartment(name, nr), numberOfMothers(mother), numberOfNewborns(newborn), averageGrade(grade) {};
	bool isEfficient() override;
	string toString() override;
	~NeonatalUnit() = default;

};

class Surgery :public HospitalDepartment {
private:
	int numberOfPatients;
public:
	Surgery(string name, int nr, int patients) : HospitalDepartment(name, nr), numberOfPatients(patients) {};
	bool isEfficient() override;
	string toString() override;
};
