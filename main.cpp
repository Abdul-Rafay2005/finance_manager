#include <QApplication>
#include "loginwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWindow login;
    MainWindow mainWin;

    QObject::connect(&login, &LoginWindow::loginSuccess, [&]() {
        mainWin.show();
    });

    login.show();
    return app.exec();
}
