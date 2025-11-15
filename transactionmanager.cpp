// #include "transactionmanager.h"
// #include <algorithm>
// #include <QFile>
// #include <QJsonDocument>
// #include <QJsonArray>
// #include <QJsonObject>
// #include <QSet>
// #include <QDebug>
// #include <QDate> // Ensure QDate is available

// // Assuming transaction.h defines Transaction::operator==, Transaction::toJson(), and Transaction::fromJson()

// TransactionManager::TransactionManager() {}

// void TransactionManager::addTransaction(const Transaction &t)
// {
//     transactions.append(t);
// }

// void TransactionManager::removeTransaction(const Transaction &t)
// {
//     transactions.removeOne(t);
// }

// void TransactionManager::updateTransaction(const Transaction &original, const Transaction &updated)
// {
//     int index = transactions.indexOf(original);
//     if (index != -1) {
//         transactions[index] = updated;
//     }
// }

// void TransactionManager::sortByDate()
// {
//     std::sort(transactions.begin(), transactions.end(),
//               [](const Transaction &a, const Transaction &b) {
//                   return a.date > b.date;
//               });
// }

// const QList<Transaction>& TransactionManager::getTransactions() const
// {
//     return transactions;
// }

// QList<Transaction> TransactionManager::getFilteredTransactions(const QDate &start, const QDate &end) const
// {
//     QList<Transaction> filtered;
//     for (const auto &t : transactions) {
//         if (t.date >= start && t.date <= end) {
//             filtered.append(t);
//         }
//     }
//     return filtered;
// }

// QStringList TransactionManager::getAllCategories(const QString &type) const
// {
//     QSet<QString> categories;
//     for (const auto &t : transactions) {
//         if (t.type == type) {
//             categories.insert(t.category);
//         }
//     }
//     return QStringList(categories.values());
// }

// double TransactionManager::getTotalIncome() const
// {
//     double total = 0.0;
//     for (const auto &t : transactions) {
//         if (t.type == "Income") {
//             total += t.amount;
//         }
//     }
//     return total;
// }

// double TransactionManager::getTotalExpense() const
// {
//     double total = 0.0;
//     for (const auto &t : transactions) {
//         if (t.type == "Expense") {
//             total += t.amount;
//         }
//     }
//     return total;
// }

// double TransactionManager::getBalance() const
// {
//     return getTotalIncome() - getTotalExpense();
// }

// // FIX: Returns bool and includes logic to return success/failure status.
// bool TransactionManager::saveToFile(const QString &fileName) const
// {
//     QJsonArray transactionsArray;
//     for (const auto &t : transactions) {
//         transactionsArray.append(t.toJson());
//     }

//     QJsonDocument doc(transactionsArray);
//     QFile file(fileName);

//     if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//         qWarning() << "Couldn't open save file:" << fileName;
//         return false;
//     }

//     qint64 bytesWritten = file.write(doc.toJson());
//     file.close();

//     return bytesWritten > 0;
// }

// // FIX: Returns bool and includes logic to return success/failure status.
// bool TransactionManager::loadFromFile(const QString &fileName)
// {
//     QFile file(fileName);
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         return false; // File not found or couldn't be opened
//     }

//     QByteArray data = file.readAll();
//     file.close();

//     QJsonDocument doc = QJsonDocument::fromJson(data);

//     if (doc.isNull() || !doc.isArray()) {
//         qWarning() << "Failed to parse JSON file or file is empty/invalid.";
//         return false;
//     }

//     QJsonArray transactionsArray = doc.array();

//     transactions.clear();
//     for (const auto &val : transactionsArray) {
//         if (val.isObject()) {
//             // Assuming Transaction::fromJson handles data integrity
//             transactions.append(Transaction::fromJson(val.toObject()));
//         }
//     }

//     return true;
// }

#include "transactionmanager.h"
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSet>
#include <QDebug>
#include <QDate>
#include <QLocale>

TransactionManager::TransactionManager() {}

void TransactionManager::addTransaction(const Transaction &t)
{
    transactions.append(t);
}

void TransactionManager::removeTransaction(const QUuid &id)
{
    auto it = std::remove_if(transactions.begin(), transactions.end(),
                             [&id](const Transaction &t) {
                                 return t.id == id;
                             });
    transactions.erase(it, transactions.end());
}

void TransactionManager::updateTransaction(const QUuid &id, const Transaction &updated)
{
    for (int i = 0; i < transactions.size(); ++i) {
        if (transactions[i].id == id) {
            // Found the old transaction; replace it entirely, preserving the original ID.
            transactions[i] = updated;
            transactions[i].id = id;
            break;
        }
    }
}

Transaction TransactionManager::getTransactionById(const QUuid &id) const
{
    for (const auto &t : transactions) {
        if (t.id == id) {
            return t;
        }
    }
    // Return a default, invalid transaction if not found
    return Transaction();
}

void TransactionManager::sortByDate()
{
    std::sort(transactions.begin(), transactions.end(),
              [](const Transaction &a, const Transaction &b) {
                  return a.date > b.date; // Latest date first
              });
}

const QList<Transaction>& TransactionManager::getTransactions() const
{
    return transactions;
}

QList<Transaction> TransactionManager::getFilteredTransactions(const QDate &start, const QDate &end) const
{
    QList<Transaction> filtered;
    for (const auto &t : transactions) {
        if (t.date >= start && t.date <= end) {
            filtered.append(t);
        }
    }
    return filtered;
}

QStringList TransactionManager::getAllCategories(const QString &type) const
{
    QSet<QString> categories;
    for (const auto &t : transactions) {
        if (t.type == type) {
            categories.insert(t.category);
        }
    }
    return QStringList(categories.values());
}

double TransactionManager::getTotalIncome() const
{
    double total = 0.0;
    for (const auto &t : transactions) {
        if (t.type == "Income") {
            total += t.amount;
        }
    }
    return total;
}

double TransactionManager::getTotalExpense() const
{
    double total = 0.0;
    for (const auto &t : transactions) {
        if (t.type == "Expense") {
            total += t.amount;
        }
    }
    return total;
}

double TransactionManager::getBalance() const
{
    return getTotalIncome() - getTotalExpense();
}

// --- CSV EXPORT LOGIC ---

bool TransactionManager::exportToCsv(const QString &fileName) const
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "Error opening file for export:" << fileName;
        return false;
    }

    QTextStream out(&file);

    // 1. Write the header row
    out << "Type,Category,Amount,Date,Note\n";

    // 2. Write the data rows
    for (const auto &t : transactions) {
        QString cleanNote = t.note;
        cleanNote.replace('"', "\"\"");
        cleanNote.prepend('"').append('"');

        out << t.type << ","
            << t.category << ","
            << QLocale::c().toString(t.amount, 'f', 2) << ","
            << t.date.toString(Qt::ISODate) << ","
            << cleanNote << "\n";
    }

    file.close();
    return true;
}


// --- CSV IMPORT LOGIC ---

bool TransactionManager::importFromCsv(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening file for import:" << fileName;
        return false;
    }

    QTextStream in(&file);
    int importedCount = 0;

    // Read and discard the header line
    if (!in.atEnd()) {
        in.readLine();
    }

    while (!in.atEnd()) {
        QString line = in.readLine();

        // Simple comma split
        QStringList parts = line.split(',');

        if (parts.size() < 5) {
            qWarning() << "Skipping incomplete CSV line:" << line;
            continue;
        }

        // 1. Extract and validate data
        QString type = parts[0].trimmed();
        QString category = parts[1].trimmed();
        double amount = QLocale::c().toDouble(parts[2].trimmed());
        QDate date = QDate::fromString(parts[3].trimmed(), Qt::ISODate);

        QString note = parts.mid(4).join(',').trimmed();

        // Basic validation
        if ((type != "Income" && type != "Expense") || amount <= 0.0 || !date.isValid()) {
            qWarning() << "Skipping invalid transaction data in CSV line:" << line;
            continue;
        }

        // 2. Remove surrounding quotes and unescape quotes for the note
        if (note.startsWith('"') && note.endsWith('"')) {
            note = note.mid(1, note.length() - 2);
            // FIX FOR AMBIGUOUS REPLACE OVERLOAD:
            note.replace(QString("\"\""), QString('"'));
        }

        // 3. Create and add new transaction (new ID is generated automatically)
        Transaction t(type, category, amount, date, note);
        transactions.append(t);
        importedCount++;
    }

    file.close();
    qDebug() << "Successfully imported" << importedCount << "transactions.";
    return importedCount > 0;
}

// --- JSON Persistence ---

bool TransactionManager::saveToFile(const QString &fileName) const
{
    QJsonArray transactionsArray;
    for (const auto &t : transactions) {
        transactionsArray.append(t.toJson());
    }

    QJsonDocument doc(transactionsArray);
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Couldn't open save file:" << fileName;
        return false;
    }

    qint64 bytesWritten = file.write(doc.toJson());
    file.close();

    return bytesWritten > 0;
}

bool TransactionManager::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull() || !doc.isArray()) {
        qWarning() << "Failed to parse JSON file or file is empty/invalid.";
        return false;
    }

    QJsonArray transactionsArray = doc.array();

    transactions.clear();
    for (const auto &val : transactionsArray) {
        if (val.isObject()) {
            transactions.append(Transaction::fromJson(val.toObject()));
        }
    }

    return true;
}
