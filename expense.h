#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <iostream>  // For std::cout and std::endl

class Record {
public:
    virtual ~Record() = default; // Virtual destructor
    virtual void display() const = 0; // Pure virtual function
};

class Expense : public Record {
private:
    std::string category;
    double amount;
    std::string date;

public:
    // Constructor
    Expense(const std::string& category, double amount, const std::string& date);

    // Getters
    std::string getCategory() const;
    double getAmount() const;
    std::string getDate() const;

    // Setters
    void setCategory(const std::string& newCategory);
    void setAmount(double newAmount);
    void setDate(const std::string& newDate);

    // Display functions
    void displayExpense() const;
    void display() const override;
};

#endif // EXPENSE_H
