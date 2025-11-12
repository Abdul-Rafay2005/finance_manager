#include "include/CategoryDialog.h"
#include "ui_CategoryDialog.h"
#include "include/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

CategoryDialog::CategoryDialog(int userId, QWidget *parent)
    : QDialog(parent), ui(new Ui::CategoryDialog), m_userId(userId)
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &CategoryDialog::onAddCategory);
    loadCategories();
}

CategoryDialog::~CategoryDialog()
{
    delete ui;
}

void CategoryDialog::loadCategories()
{
    ui->listCategories->clear();
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare("SELECT name, type FROM categories WHERE user_id = ?");
    q.addBindValue(m_userId);
    if (!q.exec()) {
        qWarning() << "Failed to load categories:" << q.lastError().text();
        return;
    }
    while (q.next()) {
        ui->listCategories->addItem(q.value("name").toString() + " (" + q.value("type").toString() + ")");
    }
}

void CategoryDialog::onAddCategory()
{
    QString name = ui->editName->text().trimmed();
    QString type = ui->comboType->currentText();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input", "Enter category name.");
        return;
    }
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare("INSERT INTO categories (user_id, name, type) VALUES (?, ?, ?)");
    q.addBindValue(m_userId);
    q.addBindValue(name);
    q.addBindValue(type);
    if (!q.exec()) {
        QMessageBox::warning(this, "DB Error", "Could not add category.");
        return;
    }
    ui->editName->clear();
    loadCategories();
}
