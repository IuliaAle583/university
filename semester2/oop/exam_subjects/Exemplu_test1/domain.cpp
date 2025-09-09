#include "domain.h"


Car::Car()
{
	this->color = "0";
	this->model = "0";
	this->name = "0";
	this->year = 0;
};

Car::Car(std::string name, std::string model, int year, std::string color)
{
	this->name = name;
	this->color = color;
	this->model = model;
	this->year = year;
};

void Car::set_name(const std::string& name)
{
	this->name = name;
}

void Car::set_model(const std::string& model)
{
	this->model = model;
}

void Car::set_year(int year)
{
	this->year = year;
}

void Car::set_color(const std::string& color)
{
	this->color = color;
}

std::string Car::get_name() const
{
	return this->name;
	//return std::string();
}

std::string Car::get_model() const
{
	//return std::string();
	return this->model;
}

std::string Car::get_color() const
{
	//return std::string();
	return this->color;
}

int Car::get_year() const
{
	return this->year;
}

bool Car::operator==(const Car& car)
{
	//return false;
	if (this->color == car.color && this->model == car.model && this->name == car.name && this->year == car.year) {
		return true;
	}
	return false;
}
