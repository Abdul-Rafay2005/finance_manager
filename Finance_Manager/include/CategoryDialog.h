#ifndef CATEGORYDIALOG_H
#define CATEGORYDIALOG_H

#include <QDialog>

namespace Ui { class CategoryDialog; }

class CategoryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CategoryDialog(int userId, QWidget *parent = nullptr);
    ~CategoryDialog();

private slots:
    void onAddCategory();

private:
    Ui::CategoryDialog *ui;
    int m_userId;
    void loadCategories();
};

#endif // CATEGORYDIALOG_H
