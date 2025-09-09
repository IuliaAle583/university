#pragma once
#include <string>

class Bill {
private:
	std::string serialNumber;
	std::string companyName;
	bool isPaid;
	double sum;
public:
	Bill();
	Bill(std::string serialNumber, std::string companyName, bool isPaid, double sum);
	//aici nu sunt cu & deci pot sa le scriu direct

	std::string getNumber() const;
	std::string getName() const;
	bool getPaid() const;
	double getSum() const;

	void setNumber(const std::string& number);
	void setName(const std::string& name);
	void setPaid(bool paid);
	void setSum(double sum);
};
