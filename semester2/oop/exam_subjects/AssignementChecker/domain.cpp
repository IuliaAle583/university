#include "domain.h"

Assignment::Assignment()
{
	this->id = 0;
	this->name = "0";
	this->solution = "0";
}

Assignment::Assignment(int id, const std::string& name, const std::string& solution)
{
	this->id = id;
	this->name = name;
	this->solution = solution;
}

void Assignment::setId(int id)
{
	this->id = id;
}

void Assignment::setName(std::string name)
{
	this->name = name;
}

void Assignment::setSolution(std::string solution)
{
	this->solution = solution;
}

int Assignment::getId()
{
	return this->id;
}

std::string Assignment::getName()
{
	return this->name;
}

std::string Assignment::getSolution()
{
	return this->solution;
}
