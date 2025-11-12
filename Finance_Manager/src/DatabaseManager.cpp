#include "include/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager inst;
    return inst;
}

DatabaseManager::DatabaseManager()
{
}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isOpen()) m_db.close();
}

bool DatabaseManager::initialize(const QString& path)
{
    if (QSqlDatabase::contains("FinanceManagerConnection")) {
        m_db = QSqlDatabase::database("FinanceManagerConnection");
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "FinanceManagerConnection");
        m_db.setDatabaseName(path);
    }

    if (!m_db.open()) {
        qWarning() << "Failed to open DB:" << m_db.lastError().text();
        return false;
    }

    createTables();
    return true;
}

QSqlDatabase DatabaseManager::database() const
{
    return m_db;
}

void DatabaseManager::createTables()
{
    QSqlQuery q(m_db);

    q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password_hash TEXT NOT NULL, "
        "email TEXT)");

    q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS categories ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "user_id INTEGER, "
        "name TEXT, "
        "type TEXT, "
        "FOREIGN KEY(user_id) REFERENCES users(id))"));

    q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "user_id INTEGER, "
        "category_id INTEGER, "
        "amount REAL, "
        "date TEXT, "
        "note TEXT, "
        "type TEXT, "
        "FOREIGN KEY(user_id) REFERENCES users(id), "
        "FOREIGN KEY(category_id) REFERENCES categories(id))"));

    q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS budgets ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "user_id INTEGER, "
        "category_id INTEGER, "
        "amount REAL, "
        "start_date TEXT, "
        "end_date TEXT, "
        "FOREIGN KEY(user_id) REFERENCES users(id), "
        "FOREIGN KEY(category_id) REFERENCES categories(id))"));
}
