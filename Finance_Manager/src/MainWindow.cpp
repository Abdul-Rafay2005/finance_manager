#include "include/MainWindow.h"
#include "ui_MainWindow.h"
#include "include/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

MainWindow::MainWindow(int userId, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_userId(userId)
{
    ui->setupUi(this);
    connect(ui->listNavigation, &QListWidget::currentRowChanged, this, &MainWindow::onNavigationChanged);
    ui->listNavigation->setCurrentRow(0);
    loadRecentTransactions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNavigationChanged()
{
    int row = ui->listNavigation->currentRow();
    ui->stackedWidget->setCurrentIndex(row);
}

void MainWindow::loadRecentTransactions()
{
    ui->tableRecent->clear();
    ui->tableRecent->setRowCount(0);
    ui->tableRecent->setColumnCount(4);
    ui->tableRecent->setHorizontalHeaderLabels(QStringList() << "Date" << "Category" << "Amount" << "Note");

    QSqlDatabase db = DatabaseManager::instance().database();
    QSqlQuery q(db);
    q.prepare("SELECT t.date, c.name, t.amount, t.note FROM transactions t LEFT JOIN categories c ON t.category_id = c.id WHERE t.user_id = ? ORDER BY t.date DESC LIMIT 20");
    q.addBindValue(m_userId);
    if (!q.exec()) {
        qWarning() << "Failed to fetch transactions:" << q.lastError().text();
        return;
    }
    int row = 0;
    while (q.next()) {
        ui->tableRecent->insertRow(row);
        ui->tableRecent->setItem(row, 0, new QTableWidgetItem(q.value(0).toString()));
        ui->tableRecent->setItem(row, 1, new QTableWidgetItem(q.value(1).toString()));
        ui->tableRecent->setItem(row, 2, new QTableWidgetItem(QString::number(q.value(2).toDouble(), 'f', 2)));
        ui->tableRecent->setItem(row, 3, new QTableWidgetItem(q.value(3).toString()));
        ++row;
    }
}
