#include <QApplication>
#include "include/DatabaseManager.h"
#include "include/LoginWindow.h"
#include "include/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Apply style sheet if exists
    QFile f(":/resources/styles.qss");
    if (f.open(QFile::ReadOnly)) {
        a.setStyleSheet(QString::fromUtf8(f.readAll()));
        f.close();
    }

    // Initialize DB
    if (!DatabaseManager::instance().initialize("financemanager.db")) {
        QMessageBox::critical(nullptr, "Database Error", "Unable to initialize the database.");
        return 1;
    }

    LoginWindow login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow w(login.currentUserId());
        w.show();
        return a.exec();
    }

    return 0;
}
