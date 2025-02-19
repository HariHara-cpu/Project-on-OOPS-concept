#include "expense.h"
#include <iostream>
#include <stdexcept> // For exception handling

// Constructor
Expense::Expense(const std::string& category, double amount, const std::string& date) {
    if (category.empty()) {
        throw std::invalid_argument("Category cannot be empty.");
    }
    if (amount < 0) {
        throw std::invalid_argument("Amount cannot be negative.");
    }
    if (date.length() != 10 || date[2] != '-' || date[5] != '-') {
        throw std::invalid_argument("Invalid date format. Expected dd-mm-yyyy.");
    }
    this->category = category;
    this->amount = amount;
    this->date = date;
}

// Getters
std::string Expense::getCategory() const { return category; }
double Expense::getAmount() const { return amount; }
std::string Expense::getDate() const { return date; }

// Setters
void Expense::setCategory(const std::string& newCategory) {
    if (newCategory.empty()) {
        throw std::invalid_argument("Category cannot be empty.");
    }
    category = newCategory;
}

void Expense::setAmount(double newAmount) {
    if (newAmount < 0) {
        throw std::invalid_argument("Amount cannot be negative.");
    }
    amount = newAmount;
}

void Expense::setDate(const std::string& newDate) {
    if (newDate.length() != 10 || newDate[2] != '-' || newDate[5] != '-') {
        throw std::invalid_argument("Invalid date format. Expected dd-mm-yyyy.");
    }
    date = newDate;
}

// Display function
void Expense::displayExpense() const {
    std::cout << "Category: " << category << ", Amount: " << amount
              << ", Date: " << date << std::endl;
}

// Override display
void Expense::display() const {
    displayExpense();
}
