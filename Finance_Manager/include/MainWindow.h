#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(int userId, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNavigationChanged();

private:
    Ui::MainWindow *ui;
    int m_userId;
    void loadRecentTransactions();
};

#endif // MAINWINDOW_H
