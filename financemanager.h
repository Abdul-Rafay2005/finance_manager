#pragma once
#include "transaction.h"
#include <vector>
#include <algorithm>

class FinanceManager {
private:
    std::vector<Transaction> transactions;

public:
    void addTransaction(const Transaction& t);
    const std::vector<Transaction>& getTransactions() const;
    double getTotalIncome() const;
    double getTotalExpense() const;
    double getBalance() const;
    void sortByDate();
};
