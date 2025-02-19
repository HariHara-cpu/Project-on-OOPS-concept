#include "financeTracker.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

// Constructor
FinanceTracker::FinanceTracker(double initialIncome) : income(initialIncome), balance(initialIncome) {}

// Add an expense
void FinanceTracker::addExpense(const std::string& category, double amount, const std::string& date) {
    if (!isValidDate(date)) {
        std::cerr << "Invalid date format. Please use dd-mm-yyyy." << std::endl;
        return;
    }
    if (balance < amount) {
        std::cerr << "Insufficient balance to add expense." << std::endl;
        return;
    }
    expenses.emplace_back(category, amount, date);
    balance -= amount;
}

// Check if the amount is within the budget
bool FinanceTracker::isWithinBudget(const std::string& category, double amount) const {
    auto it = budget.find(category);
    return it != budget.end() && amount <= it->second;
}

// Add income
void FinanceTracker::addIncome(double amount) {
    income += amount;
    balance += amount;
}

// Operator+= for adding income
void FinanceTracker::operator+=(double amount) {
    addIncome(amount);
}

// Get the current balance
double FinanceTracker::getBalance() const {
    return balance;
}

// Display expenses for a given period (start and end dates)
void FinanceTracker::displayExpensesInPeriod(const std::string& startDateStr, const std::string& endDateStr) const {
    Date startDate(startDateStr);
    Date endDate(endDateStr);

    if (!startDate.isValid() || !endDate.isValid()) {
        std::cerr << "Invalid date range." << std::endl;
        return;
    }

    std::vector<Expense> filteredExpenses;
    for (const auto& expense : expenses) {
        Date expenseDate(expense.getDate());
        if (expenseDate >= startDate && expenseDate <= endDate) {
            filteredExpenses.push_back(expense);
        }
    }

    displayExpenses(filteredExpenses);
}

// Edit an existing expense
void FinanceTracker::editExpense(const std::string& category, double amount, const std::string& newCategory, double newAmount, const std::string& newDate) {
    for (auto& expense : expenses) {
        if (expense.getCategory() == category && expense.getAmount() == amount) {
            expense.setCategory(newCategory);
            expense.setAmount(newAmount);
            expense.setDate(newDate);
            return;
        }
    }
    std::cerr << "Expense not found." << std::endl;
}

// Delete an expense
void FinanceTracker::deleteExpense(const std::string& category, double amount) {
    auto it = expenses.begin();
    while (it != expenses.end()) {
        if (it->getCategory() == category && it->getAmount() == amount) {
            expenses.erase(it);
            return;
        }
        ++it;
    }
    std::cerr << "Expense not found." << std::endl;
}

// Set a budget for a specific category
void FinanceTracker::setBudget(const std::string& category, double amount) {
    budget[category] = amount;
}

// Display the budget status
void FinanceTracker::displayBudgetStatus() const {
    std::cout << "Budget Status:" << std::endl;
    for (const auto& entry : budget) {
    const std::string& category = entry.first; 
    double limit = entry.second;
        double spent = 0.0;
        for (const auto& expense : expenses) {
            if (expense.getCategory() == category) {
                spent += expense.getAmount();
            }
        }
        std::cout << "Category: " << category
                  << ", Spent: " << std::fixed << std::setprecision(2) << spent
                  << ", Budget: " << limit
                  << ", Remaining: " << (limit - spent) << std::endl;
    }
}

// Export data to a file
void FinanceTracker::exportData(const std::string& filename) const {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Failed to open file for export." << std::endl;
        return;
    }

    outFile << "Income: " << income << std::endl;
    outFile << "Balance: " << balance << std::endl;
    outFile << "Expenses:" << std::endl;

    for (const auto& expense : expenses) {
        outFile << "Category: " << expense.getCategory()
                << ", Amount: " << expense.getAmount()
                << ", Date: " << expense.getDate() << std::endl;
    }

    outFile << "Budgets:" << std::endl;
    for (const auto& entry : budget) {
    const std::string& category = entry.first; 
    double limit = entry.second;
        outFile << "Category: " << category << ", Budget: " << limit << std::endl;
    }

    std::cout << "Data exported to " << filename << std::endl;
}

// Display daily expenses
void FinanceTracker::displayDailyExpenses(const std::string& dateStr) const {
    Date date(dateStr);
    if (!date.isValid()) {
        std::cerr << "Invalid date format." << std::endl;
        return;
    }

    std::vector<Expense> filteredExpenses;
    for (const auto& expense : expenses) {
        if (expense.getDate() == dateStr) {
            filteredExpenses.push_back(expense);
        }
    }

    displayExpenses(filteredExpenses);
}

// Display weekly expenses
void FinanceTracker::displayWeeklyExpenses(const std::string& dateStr) const {
    // Assuming 'dateStr' is the start of the week (e.g., Monday), we'll need to calculate the week range.
    // For simplicity, this implementation assumes you have the logic for week calculation.

    std::vector<Expense> filteredExpenses;
    // Add logic here to filter expenses for the week

    displayExpenses(filteredExpenses);
}

// Display monthly expenses
void FinanceTracker::displayMonthlyExpenses(const std::string& dateStr) const {
    Date date(dateStr);
    if (!date.isValid()) {
        std::cerr << "Invalid date format." << std::endl;
        return;
    }

    std::vector<Expense> filteredExpenses;
    for (const auto& expense : expenses) {
        if (expense.getDate().substr(3, 2) == dateStr.substr(3, 2) && expense.getDate().substr(6, 4) == dateStr.substr(6, 4)) {
            filteredExpenses.push_back(expense);
        }
    }

    displayExpenses(filteredExpenses);
}

// Display yearly expenses
void FinanceTracker::displayYearlyExpenses(int year) const {
    std::vector<Expense> filteredExpenses;
    for (const auto& expense : expenses) {
        if (std::stoi(expense.getDate().substr(6, 4)) == year) {
            filteredExpenses.push_back(expense);
        }
    }

    displayExpenses(filteredExpenses);
}

// Helper function to display expenses
void FinanceTracker::displayExpenses(const std::vector<Expense>& filteredExpenses) const {
    if (filteredExpenses.empty()) {
        std::cout << "No expenses to display." << std::endl;
        return;
    }

    for (const auto& expense : filteredExpenses) {
        expense.displayExpense();
    }
}

// Helper function to validate date format
bool FinanceTracker::isValidDate(const std::string& date) const {
    if (date.length() != 10 || date[2] != '-' || date[5] != '-') return false;
    return true;
}
