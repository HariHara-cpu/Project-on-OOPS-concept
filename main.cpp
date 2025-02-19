#include "FinanceTracker.h"
#include "trackerBase.h"
#include <iostream>

void displayMenu() {
    std::cout << "\n=== Personal Finance Tracker Menu ===\n";
    std::cout << "1. Add Income\n";
    std::cout << "2. Add Expense\n";
    std::cout << "3. Display Balance\n";
    std::cout << "4. Display Expenses\n";
    std::cout << "5. Edit Expense\n";
    std::cout << "6. Delete Expense\n";
    std::cout << "7. Set Budget for Category\n";
    std::cout << "8. Display Budget Status\n";
    std::cout << "9. Export Data to File\n";
    std::cout << "0. Exit\n";
    std::cout << "Select an option: ";
}

void displayExpensesMenu() {
    std::cout << "\nSelect Expense Display Type:\n";
    std::cout << "1. Daily\n";
    std::cout << "2. Weekly\n";
    std::cout << "3. Monthly\n";
    std::cout << "4. Yearly\n";
    std::cout << "5. Specific Period\n";
    std::cout << "Select an option: ";
}

int main() {
    std::cout << "Welcome to Your Personal Finance Tracker! \n";
    std::cout << "Where every penny counts and your financial goals await!\n";
    std::cout << "Let's take control of your finances and achieve your dreams!\n\n";

    double initialIncome;
    std::cout << "Enter your starting income to kick things off: ";
    std::cin >> initialIncome;

    // Use a pointer to the base class
    TrackerBase* tracker = new FinanceTracker(initialIncome);

    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Exiting program.\n";
            std::cout << "Thank you for using the Finance Tracker. Goodbye and good luck on your financial journey!\n";
            break;
        }

        switch (choice) {
            case 1: {
                double income;
                std::cout << "Enter income amount: ";
                std::cin >> income;
                tracker->addIncome(income); // Polymorphic call
                break;
            }
            case 2: {
                std::string category, date;
                double amount;
                std::cout << "Enter expense category: ";
                std::cin >> category;
                std::cout << "Enter expense amount: ";
                std::cin >> amount;
                std::cout << "Enter date (dd-mm-yyyy): ";
                std::cin >> date;
                tracker->addExpense(category, amount, date); // Polymorphic call
                break;
            }
            case 3: {
                std::cout << "Current Balance: " << tracker->getBalance() << "\n"; // Polymorphic call
                break;
            }
            case 4: {
                displayExpensesMenu();
                int displayChoice;
                std::cin >> displayChoice;

                switch (displayChoice) {
                    case 1: { // Daily
                        std::string date;
                        std::cout << "Enter date (dd-mm-yyyy): ";
                        std::cin >> date;
                        tracker->displayDailyExpenses(date); // Polymorphic call
                        break;
                    }
                    case 2: { // Weekly
                        std::string startDate;
                        std::cout << "Enter start date of the week (dd-mm-yyyy): ";
                        std::cin >> startDate;
                        tracker->displayWeeklyExpenses(startDate); // Polymorphic call
                        break;
                    }
                    case 3: { // Monthly
                        std::string date;
                        std::cout << "Enter date within the month to display (dd-mm-yyyy): ";
                        std::cin >> date;
                        tracker->displayMonthlyExpenses(date); // Polymorphic call
                        break;
                    }
                    case 4: { // Yearly
                        int year;
                        std::cout << "Enter year: ";
                        std::cin >> year;
                        tracker->displayYearlyExpenses(year); // Polymorphic call
                        break;
                    }
                    case 5: { // Specific Period
                        std::string startDate, endDate;
                        std::cout << "Enter start date (dd-mm-yyyy): ";
                        std::cin >> startDate;
                        std::cout << "Enter end date (dd-mm-yyyy): ";
                        std::cin >> endDate;
                        tracker->displayExpensesInPeriod(startDate, endDate); // Polymorphic call
                        break;
                    }
                    default:
                        std::cout << "Invalid option. Returning to main menu.\n";
                        break;
                }
                break;
            }
            case 5: {
                std::string category, newCategory, newDate;
                double amount, newAmount;
                std::cout << "Enter category of expense to edit: ";
                std::cin >> category;
                std::cout << "Enter amount of expense to edit: ";
                std::cin >> amount;
                std::cout << "Enter new category: ";
                std::cin >> newCategory;
                std::cout << "Enter new amount: ";
                std::cin >> newAmount;
                std::cout << "Enter new date (dd-mm-yyyy): ";
                std::cin >> newDate;
                tracker->editExpense(category, amount, newCategory, newAmount, newDate); // Polymorphic call
                break;
            }
            case 6: {
                std::string category;
                double amount;
                std::cout << "Enter category of expense to delete: ";
                std::cin >> category;
                std::cout << "Enter amount of expense to delete: ";
                std::cin >> amount;
                tracker->deleteExpense(category, amount); // Polymorphic call
                break;
            }
            case 7: {
                std::string category;
                double amount;
                std::cout << "Enter category for budget: ";
                std::cin >> category;
                std::cout << "Enter budget amount: ";
                std::cin >> amount;
                tracker->setBudget(category, amount); // Polymorphic call
                break;
            }
            case 8: {
                tracker->displayBudgetStatus(); // Polymorphic call
                break;
            }
            case 9: {
                std::string filename;
                std::cout << "Enter filename to export data: ";
                std::cin >> filename;
                tracker->exportData(filename); // Polymorphic call
                break;
            }
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
        }
    }

    delete tracker; // Free allocated memory
    return 0;
}
