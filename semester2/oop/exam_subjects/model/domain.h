#pragma once
#include <string>
using namespace std;

class MedicalAnalysis
{
protected:
	string date;
public:
	MedicalAnalysis(const string& date) : date(date){}
	virtual ~MedicalAnalysis() = default;
	virtual bool isResultOK() const =0;
	virtual string toString() const ;
	int getMonth() const {
		return stoi(date.substr(5, 2));
	}
	string getDate() const { return date; }
};

class BMI : public MedicalAnalysis {
private:
	double value;
public:
	BMI(const string& date, double value): MedicalAnalysis(date), value(value){}
	~BMI() = default;
	bool isResultOK() const override;
	string toString() const override;

};

class BP : public MedicalAnalysis {
private:
	int systolic;
	int diastolic;
public:
	BP(const string& date, int systolic, int diastolic): MedicalAnalysis(date), systolic(systolic), diastolic(diastolic){}
	bool isResultOK() const override;
	string toString() const  override;
	~BP() = default;

};

