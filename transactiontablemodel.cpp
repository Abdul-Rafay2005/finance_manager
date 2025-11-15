#include "transactiontablemodel.h"
#include <QColor>
#include <QFont>
#include <QLocale>
#include <QDebug>
#include <QUuid>

TransactionTableModel::TransactionTableModel(TransactionManager *manager, QObject *parent)
    : QAbstractTableModel(parent), manager(manager)
{
}

int TransactionTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return currentList.size();
}

int TransactionTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return ColumnCount;
}

QVariant TransactionTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= currentList.size())
        return QVariant();

    const Transaction &t = currentList.at(index.row());

    // --- Role: Display (The text shown in the cell) ---
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case Type: return t.type;
        case Category: return t.category;
        case Amount:
            // Format amount as currency string
            return QLocale().toCurrencyString(t.amount);
        case Date: return t.date.toString("dd-MM-yyyy");
        case Note: return t.note;
        default: return QVariant();
        }
    }

    // --- Role: Foreground (Text color) ---
    if (role == Qt::ForegroundRole && index.column() == Amount) {
        if (t.type == "Income") {
            return QColor("#2ecc71"); // Green for income
        } else {
            return QColor("#e74c3c"); // Red for expense
        }
    }

    // --- Role: Text Alignment ---
    if (role == Qt::TextAlignmentRole) {
        if (index.column() == Amount) {
            // FIX: Explicitly cast the QFlags combination to int for QVariant.
            return (int)(Qt::AlignRight | Qt::AlignVCenter);
        }
        // FIX: Explicitly cast the QFlags combination to int for QVariant.
        return (int)(Qt::AlignLeft | Qt::AlignVCenter);
    }

    return QVariant();
}

QVariant TransactionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case Type: return "Type";
        case Category: return "Category";
        case Amount: return "Amount";
        case Date: return "Date";
        case Note: return "Note";
        default: return QVariant();
        }
    }
    return QVariant();
}

void TransactionTableModel::setTransactions(const QList<Transaction> &transactions)
{
    // 1. Notify the view that the data is about to change
    beginResetModel();
    // 2. Update the internal list
    currentList = transactions;
    // 3. Notify the view that the data has changed
    endResetModel();
}

QUuid TransactionTableModel::getId(int row) const
{
    if (row >= 0 && row < currentList.size()) {
        return currentList.at(row).id;
    }
    // Return an invalid/null ID if row is out of bounds
    return QUuid();
}
