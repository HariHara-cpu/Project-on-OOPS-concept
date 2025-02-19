#ifndef TRACKERBASE_H
#define TRACKERBASE_H

#include <string>

class TrackerBase {
public:
    virtual ~TrackerBase() = default;

    // Virtual functions to be overridden by derived classes
    virtual void addIncome(double amount) = 0;
    virtual void addExpense(const std::string& category, double amount, const std::string& date) = 0;
    virtual double getBalance() const = 0;

    virtual void displayDailyExpenses(const std::string& dateStr) const = 0;
    virtual void displayWeeklyExpenses(const std::string& dateStr) const = 0;
    virtual void displayMonthlyExpenses(const std::string& dateStr) const = 0;
    virtual void displayYearlyExpenses(int year) const = 0;
    virtual void displayExpensesInPeriod(const std::string& startDateStr, const std::string& endDateStr) const = 0;

    virtual void editExpense(const std::string& category, double amount, const std::string& newCategory, 
                             double newAmount, const std::string& newDate) = 0;
    virtual void deleteExpense(const std::string& category, double amount) = 0;

    virtual void setBudget(const std::string& category, double amount) = 0;
    virtual void displayBudgetStatus() const = 0;
    virtual void exportData(const std::string& filename) const = 0;
};

#endif // TRACKERBASE_H
