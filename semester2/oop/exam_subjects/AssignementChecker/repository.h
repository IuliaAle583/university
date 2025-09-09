#pragma once
#include "dynamicVector.h"
#include "domain.h"
#include <fstream>
#include <sstream>

class Repository {
private:
	DynamicVector<Assignment> assigns;
	std::string fileName;
public:
	Repository();
	Repository(std::string fileName);
	~Repository();
	void readFromFile();
	void writeToFile();
	void add(int id, const std::string& name, const std::string& solution);
	DynamicVector<Assignment> getAll();
	//int percentage(const std::string& solution1, const std::string& solution2);
	DynamicVector<std::string> checkDishonesty();
	int countWords(const std::string& text);
	int countCommonWords(const std::string& sol1, const std::string& sol2);
};
