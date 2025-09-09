#pragma once
#include <string>
class Car {
private:
	 std::string name;
	 std::string model;
	 int year;
	 std::string color;
public:
	Car();
	Car(std::string name, std::string model, int year, std::string color);
	void set_name(const std::string& name);
	void set_model(const std::string& model);
	void set_year(int year);
	void set_color(const std::string& color);

	std::string get_name() const;
	std::string get_model() const;
	std::string get_color() const;
	int get_year() const;

	bool operator==(const Car& car);

};
