#include "domain.h"

Bill::Bill()
{
	this->companyName = "0";
	this->isPaid = 0;
	this->serialNumber = "0";
	this->sum = 0;

};

Bill::Bill(std::string serialNumber, std::string companyName, bool isPaid, double sum)
{
	this->companyName = companyName;
	this->isPaid = isPaid;
	this->serialNumber = serialNumber;
	this->sum = sum;
}

std::string Bill::getNumber() const
{
	return this->serialNumber;
}

std::string Bill::getName() const
{
	return this->companyName;
}

bool Bill::getPaid() const
{
	return this->isPaid;
}

double Bill::getSum() const
{
	return this->sum;
}

void Bill::setNumber(const std::string& number)
{
	this->serialNumber = number;
}

void Bill::setName(const std::string& name)
{
	this->companyName = name;
}

void Bill::setPaid(bool paid)
{
	this->isPaid = paid;
}

void Bill::setSum(double sum)
{
	this->sum = sum;
}


