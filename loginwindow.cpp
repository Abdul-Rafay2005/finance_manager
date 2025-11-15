#include "loginwindow.h"

// Include all necessary Qt classes
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QWidget>      // Used for the central form container
#include <QTimer>
#include <QPropertyAnimation>
#include <QPoint>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Finance Manager - Login");
    resize(420, 480); // Window size
    setupUI();
    applyStyle();
}

// ---------------------------
//  UI Setup (CORRECTED for Layout Width)
// ---------------------------
void LoginWindow::setupUI()
{
    // Initialize member variables
    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    statusLabel = new QLabel(this);
    passwordToggleBtn = new QToolButton(this);
    passwordToggleBtn->setText("👁");
    passwordToggleBtn->setCursor(Qt::PointingHandCursor);
    loginBtn = new QPushButton("LOGIN", this);

    // --- Main Layout ---
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setContentsMargins(60, 40, 60, 40);
    mainLayout->setSpacing(14);

    // --- FIX: Central Container for Width Constraint ---
    // We constrain this WIDGET, then add all form elements to its layout.
    QWidget *formContainer = new QWidget(this);
    formContainer->setMaximumWidth(350);
    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    formLayout->setSpacing(14);
    formLayout->setContentsMargins(0, 0, 0, 0);

    // --- Icon + Title ---
    QLabel *icon = new QLabel("💼", this);
    icon->setObjectName("iconLabel");
    icon->setAlignment(Qt::AlignCenter);

    QLabel *title = new QLabel("Finance Manager", this);
    title->setObjectName("titleLabel");
    title->setAlignment(Qt::AlignCenter);

    QLabel *subtitle = new QLabel("Please log in to continue", this);
    subtitle->setObjectName("subtitleLabel");
    subtitle->setAlignment(Qt::AlignCenter);

    // --- Username ---
    QLabel *userLabel = new QLabel("Username", this);
    usernameEdit->setPlaceholderText("Enter username (admin)");

    // --- Password + Eye button container ---
    QLabel *passLabel = new QLabel("Password", this);
    passwordEdit->setPlaceholderText("Enter password (1234)");
    passwordEdit->setMinimumHeight(38);

    passwordToggleBtn->setFixedSize(32, 32);

    QWidget *passwordContainer = new QWidget(this);
    QHBoxLayout *pwLayout = new QHBoxLayout(passwordContainer);
    pwLayout->setContentsMargins(0, 0, 0, 0);
    pwLayout->setSpacing(0);
    pwLayout->addWidget(passwordEdit);
    pwLayout->addWidget(passwordToggleBtn);
    passwordContainer->setObjectName("passwordContainer");

    // --- Status ---
    statusLabel->setObjectName("statusLabel");
    statusLabel->setAlignment(Qt::AlignCenter);

    // --- Assemble Form (Adding to formLayout) ---
    formLayout->addWidget(icon);
    formLayout->addWidget(title);
    formLayout->addWidget(subtitle);
    formLayout->addSpacing(20);
    formLayout->addWidget(userLabel);
    formLayout->addWidget(usernameEdit);
    formLayout->addSpacing(5);
    formLayout->addWidget(passLabel);
    formLayout->addWidget(passwordContainer);
    formLayout->addSpacing(25);
    formLayout->addWidget(loginBtn);
    formLayout->addWidget(statusLabel);

    // Add the constrained container to the main window layout
    mainLayout->addWidget(formContainer, 0, Qt::AlignCenter);

    // --- Connections ---
    connect(passwordToggleBtn, &QToolButton::clicked, this, &LoginWindow::togglePasswordVisibility);
    connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginWindow::handleLogin);
}

// ---------------------------
//  Styling (Clean, Light, Minimalist Blue)
// ---------------------------
void LoginWindow::applyStyle()
{
    setStyleSheet(R"(
        QWidget {
            /* Light gray background for the window */
            background-color: #f4f7f6;
            font-family: 'Segoe UI', 'Arial', sans-serif;
            font-size: 15px;
        }

        QLabel#titleLabel {
            font-size: 28px;
            font-weight: 700;
            color: #0A74DA; /* Corporate Blue Primary Color */
            margin-bottom: 0px;
        }
        QLabel#iconLabel {
            font-size: 48px;
            color: #0A74DA;
        }
        QLabel#subtitleLabel {
            font-size: 16px;
            color: #7f8c8d;
            font-weight: 500;
            margin-bottom: 10px;
        }
        QLabel {
            color: #333333;
            font-weight: 600;
            margin-top: 5px;
        }

        /* Flat "bottom-border" style for line edits */
        QLineEdit {
            border: none;
            border-bottom: 2px solid #bdc3c7; /* Light gray line */
            padding: 8px 2px;
            background: transparent;
            font-size: 16px;
            color: #000000
        }
        QLineEdit:focus {
            border-bottom: 2px solid #0A74DA; /* Blue line on focus */
        }

        /* Password button styling */
        QWidget#passwordContainer {
            background: transparent;
        }
        QToolButton {
            background: transparent;
            border: none;
            color: #95a5a6;
            font-size: 17px;
            margin-left: 5px;
        }
        QToolButton:hover {
            color: #0A74DA;
        }

        /* Button styling */
        QPushButton {
            background-color: #0A74DA; /* Blue */
            color: white;
            border-radius: 8px;
            padding: 12px;
            font-size: 17px;
            font-weight: 600;
            margin-top: 20px;
        }
        QPushButton:hover {
            background-color: #085FB1; /* Darker blue */
        }
        QPushButton:disabled {
            background-color: #95a5a6; /* Gray when disabled/loading */
        }
        QPushButton#successButton {
            background-color: #27ae60; /* Green on success */
        }

        QLabel#statusLabel {
            color: #e74c3c; /* Red for errors */
            font-style: italic;
            font-size: 14px;
            font-weight: 500;
            margin-top: 10px;
        }
)"
    );
}

// ---------------------------
//  Logic: Toggle Password
// ---------------------------
void LoginWindow::togglePasswordVisibility()
{
    if (passwordEdit->echoMode() == QLineEdit::Password) {
        passwordEdit->setEchoMode(QLineEdit::Normal);
        passwordToggleBtn->setText("🔒");
    } else {
        passwordEdit->setEchoMode(QLineEdit::Password);
        passwordToggleBtn->setText("👁");
    }
}

// ---------------------------
//  Logic: Handle Login
// ---------------------------
void LoginWindow::handleLogin()
{
    statusLabel->clear();
    loginBtn->setEnabled(false);
    loginBtn->setText("CHECKING...");

    // Reset object name to default state
    loginBtn->setObjectName("");
    applyStyle();

    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (username == "admin" && password == "1234") {
        // SUCCESS state
        statusLabel->clear();
        loginBtn->setObjectName("successButton");
        loginBtn->setText("✔ SUCCESS");
        applyStyle();

        QTimer::singleShot(1000, this, [this]() {
            emit loginSuccess();
            close();
        });

    } else {
        // FAILURE state
        statusLabel->setText("❌ Invalid username or password!");
        shakeWindow();
        loginBtn->setEnabled(true);
        loginBtn->setText("LOGIN");
    }
}

// ---------------------------
//  Shake Animation
// ---------------------------
void LoginWindow::shakeWindow()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    QPoint originalPos = this->pos();

    animation->setDuration(400);
    animation->setEasingCurve(QEasingCurve::Linear);

    animation->setKeyValueAt(0.0, originalPos + QPoint(-10, 0));
    animation->setKeyValueAt(0.1, originalPos + QPoint(10, 0));
    animation->setKeyValueAt(0.2, originalPos + QPoint(-10, 0));
    animation->setKeyValueAt(0.3, originalPos + QPoint(10, 0));
    animation->setKeyValueAt(0.4, originalPos + QPoint(-8, 0));
    animation->setKeyValueAt(0.5, originalPos + QPoint(8, 0));
    animation->setKeyValueAt(0.6, originalPos + QPoint(-5, 0));
    animation->setKeyValueAt(0.7, originalPos + QPoint(5, 0));
    animation->setKeyValueAt(0.8, originalPos + QPoint(-2, 0));
    animation->setKeyValueAt(0.9, originalPos + QPoint(2, 0));
    animation->setKeyValueAt(1.0, originalPos);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
