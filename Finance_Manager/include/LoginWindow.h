#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui { class LoginWindow; }

class LoginWindow : public QDialog
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    int currentUserId() const { return m_userId; }

private slots:
    void onLogin();
    void onRegister();

private:
    Ui::LoginWindow *ui;
    int m_userId{-1};
};

#endif // LOGINWINDOW_H
