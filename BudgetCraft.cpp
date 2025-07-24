#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

struct Expense {
    string date, category;
    double amount;
};

vector<Expense> readExpenses() {
    vector<Expense> expenses;
    ifstream file("expenses.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Expense e;
        getline(ss, e.date, ',');
        getline(ss, e.category, ',');
        ss >> e.amount;
        expenses.push_back(e);
    }
    return expenses;
}

void addExpense() {
    ofstream file("expenses.txt", ios::app);
    string date, category;
    double amount;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter category (Food, Travel, etc): ";
    cin >> category;
    cout << "Enter amount: ";
    cin >> amount;
    file << date << "," << category << "," << amount << endl;
    file.close();
    cout << "Expense added.\n";
}

void showSummary() {
    vector<Expense> expenses = readExpenses();
    double total = 0;
    map<string, double> categoryTotal;
    for (auto &e : expenses) {
        total += e.amount;
        categoryTotal[e.category] += e.amount;
    }

    cout << "\nTotal Expenses: Rs." << total << "\nCategory-wise Summary:\n";
    for (auto &pair : categoryTotal) {
        cout << setw(10) << pair.first << ": Rs." << pair.second << "\n";
    }
}

int main() {
    system("chcp 65001");

    int choice;
    do {
        cout << "\n==== BudgetCraft ====\n";
        cout << "1. Add Expense\n2. View Summary\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addExpense(); break;
            case 2: showSummary(); break;
            case 3: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 3);
    return 0;
}
