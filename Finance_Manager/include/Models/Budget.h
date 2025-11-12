#ifndef BUDGET_H
#define BUDGET_H

#include <QString>
#include <QDate>

struct Budget {
    int id{0};
    int userId{0};
    int categoryId{0};
    double amount{0.0};
    QDate startDate;
    QDate endDate;
};

#endif // BUDGET_H
