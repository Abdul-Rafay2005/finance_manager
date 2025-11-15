#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <QDialog>
#include "transaction.h"

// Forward declarations
class QComboBox;
class QLineEdit;
class QDateEdit;
class QDialogButtonBox;

class TransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionDialog(QWidget *parent = nullptr);

    void setTransaction(const Transaction &t);
    Transaction getTransaction() const;

    // Sets the list of categories for the combobox
    void setCategoryList(const QStringList &categories);

private slots:
    void onTypeChanged(const QString &type);

private:
    QComboBox *typeBox;
    QComboBox *categoryComboBox; // Changed from QLineEdit
    QLineEdit *amountEdit;
    QDateEdit *dateEdit;
    QLineEdit *noteEdit;
    QDialogButtonBox *buttonBox;
};

#endif // TRANSACTIONDIALOG_H
