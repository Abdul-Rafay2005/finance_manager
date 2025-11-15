#include "transactiondialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QDoubleValidator>
#include <QPushButton>

TransactionDialog::TransactionDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Add Transaction");
    setMinimumWidth(400);

    // Create widgets
    typeBox = new QComboBox;
    typeBox->addItems({"Income", "Expense"});

    categoryComboBox = new QComboBox;
    categoryComboBox->setEditable(true); // Allow user to add new categories
    categoryComboBox->setPlaceholderText("e.g., Salary, Groceries");

    amountEdit = new QLineEdit;
    amountEdit->setValidator(new QDoubleValidator(0, 9999999, 2, this));
    amountEdit->setPlaceholderText("e.g., 50.75");

    dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);

    noteEdit = new QLineEdit;
    noteEdit->setPlaceholderText("Optional note");

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    // Layout
    QFormLayout *formLayout = new QFormLayout;
    formLayout->setSpacing(15);
    formLayout->addRow("Type:", typeBox);
    formLayout->addRow("Category:", categoryComboBox);
    formLayout->addRow("Amount:", amountEdit);
    formLayout->addRow("Date:", dateEdit);
    formLayout->addRow("Note:", noteEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    // Connections
    connect(buttonBox, &QDialogButtonBox::accepted, this, &TransactionDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &TransactionDialog::reject);

    // Style (optional, but nice)
    setStyleSheet(R"(
        QDialog { background-color: #34495e; }
        QLabel { color: #ecf0f1; font-weight: 600; }
        QLineEdit, QComboBox, QDateEdit {
            border: 2px solid #2c3e50;
            border-radius: 8px; padding: 10px;
            background-color: #2c3e50; color: #ecf0f1;
        }
        QLineEdit:focus, QComboBox:focus, QDateEdit:focus { border-color: #1abc9c; }
        QPushButton {
            background-color: #1abc9c; color: white;
            border-radius: 8px; padding: 10px 15px;
            font-weight: bold;
        }
        QPushButton:hover { background-color: #16a085; }
    )");
}

// Used to pre-fill the dialog for editing
void TransactionDialog::setTransaction(const Transaction &t)
{
    setWindowTitle("Edit Transaction");
    typeBox->setCurrentText(t.type);
    categoryComboBox->setCurrentText(t.category);
    amountEdit->setText(QString::number(t.amount));
    dateEdit->setDate(t.date);
    noteEdit->setText(t.note);
}

// Used to get the data back out after "OK" is clicked
Transaction TransactionDialog::getTransaction() const
{
    return Transaction(
        typeBox->currentText(),
        categoryComboBox->currentText().trimmed(),
        amountEdit->text().toDouble(),
        dateEdit->date(),
        noteEdit->text().trimmed()
        );
}

// Sets the suggestions in the category dropdown
void TransactionDialog::setCategoryList(const QStringList &categories)
{
    categoryComboBox->clear();
    categoryComboBox->addItems(categories);
}

// We could auto-swap category lists, but we'll let MainWindow handle that
void TransactionDialog::onTypeChanged(const QString &type)
{
    // This logic is now handled by MainWindow before showing the dialog
}
