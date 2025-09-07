#pragma once
#include <string>
using namespace std;

struct Date {
    int day;
    int month;
    int year;

    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    bool operator==(const Date& date) const;
    bool operator<(const Date& date) const;
    bool operator>(const Date& date) const;
};

Date parseDate(const std::string& str);
//Date::operator<(const Date& other);
//bool Date::operator==(const Date& other) const;

class School {
private:
	string name;
	string address;
    Date d;
    bool value;
public:
    School() : name(""), address(""), d(), value(false) {}

    School(std::string n, std::string a, Date date, bool v)
        : name(n), address(a), d(date), value(v) {}

    Date getDate() const { return d; }
    void setDate(const Date& date) { d = date; }
    
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    //Date getDate() const { return d; }
    bool getValue() const { return value; }

    void setName(const std::string& n) { name = n; }
    void setAddress(const std::string& a) { address = a; }
    //void setDate(const Date& date) { d = date; }
    void setValue(bool v) { value = v; }

};