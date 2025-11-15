#ifndef TRANSACTIONTABLEMODEL_H
#define TRANSACTIONTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "transactionmanager.h" // Access to manager and Transaction struct

class TransactionTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TransactionTableModel(TransactionManager *manager, QObject *parent = nullptr);

    // Basic required functions for QAbstractTableModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Custom functions to refresh data
    void setTransactions(const QList<Transaction> &transactions);
    QUuid getId(int row) const; // New: Get the ID of a row

private:
    TransactionManager *manager;
    QList<Transaction> currentList; // The filtered list displayed in the table

    enum Columns {
        Type = 0,
        Category = 1,
        Amount = 2,
        Date = 3,
        Note = 4,
        ColumnCount // Total number of columns
    };
};

#endif // TRANSACTIONTABLEMODEL_H
