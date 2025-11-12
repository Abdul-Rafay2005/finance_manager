#include "include/UserManager.h"
#include "include/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QVariant>
#include <QDebug>

QString UserManager::hashPassword(const QString &password)
{
    QByteArray b = password.toUtf8();
    QByteArray hashed = QCryptographicHash::hash(b, QCryptographicHash::Sha256);
    return QString(hashed.toHex());
}

bool UserManager::registerUser(const QString &username, const QString &password, const QString &email)
{
    QSqlDatabase db = DatabaseManager::instance().database();
    QSqlQuery q(db);
    q.prepare("INSERT INTO users (username, password_hash, email) VALUES (?, ?, ?)");
    q.addBindValue(username);
    q.addBindValue(hashPassword(password));
    q.addBindValue(email);
    if (!q.exec()) {
        qWarning() << "Register failed:" << q.lastError().text();
        return false;
    }
    return true;
}

int UserManager::loginUser(const QString &username, const QString &password)
{
    QSqlDatabase db = DatabaseManager::instance().database();
    QSqlQuery q(db);
    q.prepare("SELECT id, password_hash FROM users WHERE username = ?");
    q.addBindValue(username);
    if (!q.exec()) {
        qWarning() << "Login query failed:" << q.lastError().text();
        return -1;
    }
    if (q.next()) {
        QString storedHash = q.value("password_hash").toString();
        if (storedHash == hashPassword(password)) {
            return q.value("id").toInt();
        }
    }
    return -1;
}
