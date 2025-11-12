#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDate>

struct Transaction {
    int id{0};
    int userId{0};
    int categoryId{0};
    double amount{0.0};
    QDate date;
    QString note;
    QString type; // "income" or "expense"
};

#endif // TRANSACTION_H
