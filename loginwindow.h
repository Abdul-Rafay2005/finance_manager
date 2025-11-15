#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

// Forward declarations for pointers
class QLineEdit;
class QLabel;
class QToolButton;
class QPushButton;

class LoginWindow : public QWidget
{
    Q_OBJECT // Essential for signals and slots

public:
    explicit LoginWindow(QWidget *parent = nullptr);

signals:
    // Emitted when credentials are correct
    void loginSuccess();

private slots:
    // Slots to handle user interaction
    void togglePasswordVisibility();
    void handleLogin();

private:
    // Private helper functions
    void setupUI();
    void applyStyle();
    void shakeWindow(); // Animation for login failure

    // Pointers to UI elements
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLabel *statusLabel;
    QToolButton *passwordToggleBtn;
    QPushButton *loginBtn;
};

#endif // LOGINWINDOW_H
