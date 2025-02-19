#ifndef DATE_H
#define DATE_H

#include <string>
#include <stdexcept>

class BaseDate {
public:
    virtual ~BaseDate() = default; // Virtual destructor for a polymorphic base class
    virtual std::string toString() const = 0; // Pure virtual function
};

class Date : public BaseDate {
private:
    int day, month, year;

public:
    // Constructors
    Date(int y, int m, int d);
    Date(const std::string& dateStr);

    // Getter methods
    int getYear() const;
    int getMonth() const;
    int getDay() const;

    // Other methods
    bool isValid() const;
    bool operator>=(const Date& other) const;
    bool operator<=(const Date& other) const;

    static int stringToInt(const std::string& str);
    std::string toString() const override; // Override the pure virtual function
};

#endif // DATE_H
