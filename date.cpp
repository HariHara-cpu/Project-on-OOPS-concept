#include "date.h"
#include <sstream>
#include <iomanip>

// Constructor definitions
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

Date::Date(const std::string& dateStr) {
    if (dateStr.length() != 10 || dateStr[2] != '-' || dateStr[5] != '-') {
        throw std::invalid_argument("Invalid date format. Expected dd-mm-yyyy.");
    }
    day = stringToInt(dateStr.substr(0, 2));
    month = stringToInt(dateStr.substr(3, 2));
    year = stringToInt(dateStr.substr(6, 4));
}

// Getter methods
int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }

// Utility methods
bool Date::isValid() const {
    // Basic validation
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) return false;
    // Handle months with fewer than 31 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    // February and leap year check
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) return false;
    }
    return true;
}

bool Date::operator>=(const Date& other) const {
    if (year > other.year) return true;
    if (year == other.year && month > other.month) return true;
    return year == other.year && month == other.month && day >= other.day;
}

bool Date::operator<=(const Date& other) const {
    if (year < other.year) return true;
    if (year == other.year && month < other.month) return true;
    return year == other.year && month == other.month && day <= other.day;
}

int Date::stringToInt(const std::string& str) {
    return std::stoi(str);
}

// Override toString
std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << day << '-'
        << std::setw(2) << std::setfill('0') << month << '-'
        << year;
    return oss.str();
}
