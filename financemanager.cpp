#include "financemanager.h"

void FinanceManager::addTransaction(const Transaction& t) {
    transactions.push_back(t);
}

const std::vector<Transaction>& FinanceManager::getTransactions() const {
    return transactions;
}

double FinanceManager::getTotalIncome() const {
    double sum = 0;
    for (const auto& t : transactions)
        if (t.type == "Income") sum += t.amount;
    return sum;
}

double FinanceManager::getTotalExpense() const {
    double sum = 0;
    for (const auto& t : transactions)
        if (t.type == "Expense") sum += t.amount;
    return sum;
}

double FinanceManager::getBalance() const {
    return getTotalIncome() - getTotalExpense();
}

// Custom sort by date using lambda
void FinanceManager::sortByDate() {
    std::sort(transactions.begin(), transactions.end(),
              [](const Transaction& a, const Transaction& b) {
                  return a.date < b.date;
              });
}
