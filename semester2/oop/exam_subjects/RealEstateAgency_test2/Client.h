#pragma once
#include "Dwelling.h"
class Client
{
protected:
	string name;
	double salary;
public:
	Client(string name = "0", double salary = 0) : name(name), salary(salary) {};
	~Client() = default;
	virtual double totalIncome() { return this->salary; };
	virtual string toString();
	virtual bool isInterested(Dwelling d)=0;
	string getName() { return this->name; };
};

class NormalClient : public Client {
public:
	NormalClient(string name = "0", double salary = 0) : Client(name, salary) {};
	~NormalClient() = default;
	bool isInterested(Dwelling d) override;
};

class WealthyClient : public Client {
private:
	double moneyFromInvestments;
public:
	WealthyClient(string name = "0", double salary = 0, double inv=0) : Client(name, salary), moneyFromInvestments(inv) {};
	double totalIncome() override;
	string toString() override;
	bool isInterested(Dwelling d) override;
	~WealthyClient() = default;
};

