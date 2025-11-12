#include "include/TransactionDialog.h"
#include "ui_TransactionDialog.h"
#include "include/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TransactionDialog::TransactionDialog(int userId, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::TransactionDialog),
    m_userId(userId)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    connect(ui->btnOk, &QPushButton::clicked, this, &TransactionDialog::onAccept);
    connect(ui->btnCancel, &QPushButton::clicked, this, &TransactionDialog::reject);
    loadCategories();
}

TransactionDialog::~TransactionDialog()
{
    delete ui;
}

void TransactionDialog::loadCategories()
{
    ui->comboCategory->clear();
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare("SELECT id, name FROM categories WHERE user_id = ? AND type = ?");
    q.addBindValue(m_userId);
    q.addBindValue(ui->comboType->currentText());
    if (!q.exec()) {
        qWarning() << "Failed to load categories:" << q.lastError().text();
        return;
    }
    while (q.next()) {
        ui->comboCategory->addItem(q.value("name").toString(), q.value("id"));
    }
}

void TransactionDialog::onAccept()
{
    bool ok;
    double amount = ui->editAmount->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input", "Enter a valid amount.");
        return;
    }
    m_transaction.userId = m_userId;
    m_transaction.amount = amount;
    m_transaction.date = ui->dateEdit->date();
    m_transaction.note = ui->editNote->text();
    m_transaction.type = ui->comboType->currentText();
    m_transaction.categoryId = ui->comboCategory->currentData().toInt();

    // Insert into DB
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare("INSERT INTO transactions (user_id, category_id, amount, date, note, type) VALUES (?, ?, ?, ?, ?, ?)");
    q.addBindValue(m_transaction.userId);
    q.addBindValue(m_transaction.categoryId);
    q.addBindValue(m_transaction.amount);
    q.addBindValue(m_transaction.date.toString(Qt::ISODate));
    q.addBindValue(m_transaction.note);
    q.addBindValue(m_transaction.type);
    if (!q.exec()) {
        QMessageBox::warning(this, "DB Error", "Could not save transaction.");
        return;
    }
    accept();
}

Transaction TransactionDialog::transaction() const { return m_transaction; }
