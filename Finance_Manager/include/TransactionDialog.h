#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <QDialog>
#include "include/Models/Transaction.h"

namespace Ui { class TransactionDialog; }

class TransactionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TransactionDialog(int userId, QWidget *parent = nullptr);
    ~TransactionDialog();
    Transaction transaction() const;

private slots:
    void onAccept();

private:
    Ui::TransactionDialog *ui;
    Transaction m_transaction;
    int m_userId;
    void loadCategories();
};

#endif // TRANSACTIONDIALOG_H
