#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QVariant>

class DatabaseManager {
public:
    static DatabaseManager& instance();
    bool initialize(const QString& path);
    QSqlDatabase database() const;
private:
    DatabaseManager();
    ~DatabaseManager();
    QSqlDatabase m_db;
    void createTables();
};

#endif // DATABASEMANAGER_H
