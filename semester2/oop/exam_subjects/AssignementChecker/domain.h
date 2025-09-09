#pragma once
#include <string>
class Assignment {
private:
	int id;
	std::string name;
	std::string solution;
public:
	Assignment();
	Assignment(int id, const std::string& name, const std::string& solution);
	void setId(int id);
	void setName(std::string name);
	void setSolution(std::string solution);

	int getId();
	std::string getName();
	std::string getSolution();
};
