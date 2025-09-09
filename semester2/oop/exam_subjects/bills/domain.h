#pragma once
#include <iostream>
#include <string>
using namespace std;
class Bill {
private:
	string companyName, code;
	double sum;
	bool isPaid;
public:
	Bill(string companyName = "", string code = "", double sum = 0.0, bool isPaid = false) : companyName(companyName), code(code), sum(sum), isPaid(isPaid) {};
	string getCompanyName() const { return this->companyName; };
	string getCode() const { return this->code; };
	string toString() const {
		string isPaidString = isPaid == true ? "true" : "false";
		return this->companyName + " " + to_string(sum);
	}
	bool getIsPaid() const{ return this->isPaid; };
	double getSum() const { return this->sum; };
	// for sorting is the following function
	inline bool operator <(const Bill& bill) const {
		return this->companyName < bill.getCompanyName();
	}
};