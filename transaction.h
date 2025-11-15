// #ifndef TRANSACTION_H
// #define TRANSACTION_H

// #include <QString>
// #include <QDate>
// #include <QJsonObject>

// struct Transaction {
//     QString type;
//     QString category;
//     double amount;
//     QDate date;
//     QString note;

//     // Default constructor
//     Transaction() : amount(0.0) {}

//     // Main constructor
//     Transaction(QString t, QString c, double a, QDate d, QString n)
//         : type(t), category(c), amount(a), date(d), note(n) {}

//     // NEW: Equality operator
//     // Needed to find and replace transactions
//     bool operator==(const Transaction &other) const {
//         return type == other.type &&
//                category == other.category &&
//                amount == other.amount && // Be careful with double comparison, but good enough here
//                date == other.date &&
//                note == other.note;
//     }

//     // --- Functions for saving/loading ---
//     QJsonObject toJson() const {
//         QJsonObject obj;
//         obj["type"] = type;
//         obj["category"] = category;
//         obj["amount"] = amount;
//         obj["date"] = date.toString(Qt::ISODate);
//         obj["note"] = note;
//         return obj;
//     }

//     static Transaction fromJson(const QJsonObject &obj) {
//         return Transaction(
//             obj["type"].toString(),
//             obj["category"].toString(),
//             obj["amount"].toDouble(),
//             QDate::fromString(obj["date"].toString(), Qt::ISODate),
//             obj["note"].toString()
//             );
//     }
// };

// #endif // TRANSACTION_H




#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDate>
#include <QJsonObject>
#include <QUuid>

struct Transaction {
    QUuid id; // NEW: Unique identifier
    QString type;
    QString category;
    double amount;
    QDate date;
    QString note;

    // Default constructor (for loading)
    Transaction() : amount(0.0) {}

    // Main constructor (generates a new ID)
    Transaction(QString t, QString c, double a, QDate d, QString n)
        : id(QUuid::createUuid()), type(t), category(c), amount(a), date(d), note(n) {}

    // Constructor for loading existing data (with ID)
    Transaction(QUuid uid, QString t, QString c, double a, QDate d, QString n)
        : id(uid), type(t), category(c), amount(a), date(d), note(n) {}

    // Equality operator: NOW ONLY CHECKS THE ID for manager lookups
    bool operator==(const Transaction &other) const {
        return id == other.id;
    }

    // --- Functions for saving/loading ---
    QJsonObject toJson() const {
        QJsonObject obj;
        obj["id"] = id.toString(); // Save ID as a string
        obj["type"] = type;
        obj["category"] = category;
        obj["amount"] = amount;
        obj["date"] = date.toString(Qt::ISODate);
        obj["note"] = note;
        return obj;
    }

    static Transaction fromJson(const QJsonObject &obj) {
        return Transaction(
            QUuid(obj["id"].toString()), // Load ID from string
            obj["type"].toString(),
            obj["category"].toString(),
            obj["amount"].toDouble(),
            QDate::fromString(obj["date"].toString(), Qt::ISODate),
            obj["note"].toString()
            );
    }
};

#endif // TRANSACTION_H
