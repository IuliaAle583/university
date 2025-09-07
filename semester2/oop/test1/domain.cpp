#include "domain.h"

Date parseDate(const std::string& str) {
    Date d;
    d.day = std::stoi(str.substr(0, 2));
    d.month = std::stoi(str.substr(3, 2));
    d.year = std::stoi(str.substr(6, 4));
    return d;
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator>(const Date& other) const {
    if (year != other.year) return year > other.year;
    if (month != other.month) return month > other.month;
    return day > other.day;
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}