#ifndef FINANCETRACKER_H
#define FINANCETRACKER_H

#include <string>
#include <vector>
#include <map>
#include "date.h"
#include "expense.h"
#include"trackerBase.h"

// Derived class FinanceTracker
class FinanceTracker : public TrackerBase  {
public:
    FinanceTracker(double initialIncome);

    void addExpense(const std::string& category, double amount, const std::string& date);
    bool isWithinBudget(const std::string& category, double amount) const;
    void addIncome(double amount);
    void operator+=(double amount);
    double getBalance() const;

    void displayExpensesInPeriod(const std::string& startDateStr, const std::string& endDateStr) const;
    void editExpense(const std::string& category, double amount, const std::string& newCategory, double newAmount, const std::string& newDate);
    void deleteExpense(const std::string& category, double amount);
    void setBudget(const std::string& category, double amount);
    void displayBudgetStatus() const override; // Override the pure virtual function
    void exportData(const std::string& filename) const;

    void displayDailyExpenses(const std::string& dateStr) const;
    void displayWeeklyExpenses(const std::string& dateStr) const;
    void displayMonthlyExpenses(const std::string& dateStr) const;
    void displayYearlyExpenses(int year) const;

private:
    double income;
    double balance;
    std::vector<Expense> expenses;
    std::map<std::string, double> budget;

    bool isValidDate(const std::string& date) const;
    void displayExpenses(const std::vector<Expense>& filteredExpenses) const;
};

#endif // FINANCETRACKER_H
