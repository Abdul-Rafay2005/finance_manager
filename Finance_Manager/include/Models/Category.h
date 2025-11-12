#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

struct Category {
    int id{0};
    int userId{0};
    QString name;
    QString type; // "income" or "expense"
};

#endif // CATEGORY_H
