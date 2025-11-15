// #ifndef TRANSACTIONMANAGER_H
// #define TRANSACTIONMANAGER_H

// #include "transaction.h"
// #include <QList>
// #include <QString>
// #include <QStringList>
// #include <QDate> // Include QDate for filtering methods

// class TransactionManager
// {
// public:
//     TransactionManager();

//     void addTransaction(const Transaction &t);
//     void removeTransaction(const Transaction &t);
//     void updateTransaction(const Transaction &original, const Transaction &updated);

//     void sortByDate();

//     const QList<Transaction>& getTransactions() const;
//     QList<Transaction> getFilteredTransactions(const QDate &start, const QDate &end) const;

//     double getTotalIncome() const;
//     double getTotalExpense() const;
//     double getBalance() const;

//     QStringList getAllCategories(const QString &type) const;

//     // --- FIX: Change return type from 'void' to 'bool' ---
//     bool saveToFile(const QString &fileName) const;
//     bool loadFromFile(const QString &fileName);
//     // -----------------------------------------------------

// private:
//     QList<Transaction> transactions;

// };

// #endif // TRANSACTIONMANAGER_H


#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include "transaction.h"
#include <QList>
#include <QString>
#include <QStringList>
#include <QDate>
#include <QUuid>

class TransactionManager
{
public:
    TransactionManager();

    void addTransaction(const Transaction &t);
    void removeTransaction(const QUuid &id);
    void updateTransaction(const QUuid &id, const Transaction &updated);

    void sortByDate();

    const QList<Transaction>& getTransactions() const;
    QList<Transaction> getFilteredTransactions(const QDate &start, const QDate &end) const;

    Transaction getTransactionById(const QUuid &id) const;

    double getTotalIncome() const;
    double getTotalExpense() const;
    double getBalance() const;

    QStringList getAllCategories(const QString &type) const;

    // --- NEW: CSV Import/Export Functions ---
    bool exportToCsv(const QString &fileName) const;
    bool importFromCsv(const QString &fileName);
    // ------------------------------------------

    bool saveToFile(const QString &fileName) const;
    bool loadFromFile(const QString &fileName);

private:
    QList<Transaction> transactions;
};

#endif // TRANSACTIONMANAGER_H
