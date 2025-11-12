#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>

class UserManager {
public:
    static bool registerUser(const QString& username, const QString& password, const QString& email = QString());
    static int loginUser(const QString& username, const QString& password); // returns user id or -1
    static QString hashPassword(const QString& password);
};

#endif // USERMANAGER_H
