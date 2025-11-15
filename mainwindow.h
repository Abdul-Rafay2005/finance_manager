// #ifndef MAINWINDOW_H
// #define MAINWINDOW_H

// #include <QMainWindow>

// // Core Data Files
// #include "transactionmanager.h" // Needed for member 'manager'
// #include "transaction.h"        // Needed for QList<Transaction>

// // Qt UI Headers
// #include <QAction>
// #include <QTableWidget>
// #include <QLabel>
// #include <QDateEdit>
// #include <QVBoxLayout>
// #include <QCloseEvent>
// #include <stdexcept>

// // Forward declaration for UI namespace (standard Qt practice)
// QT_BEGIN_NAMESPACE
// namespace Ui { class MainWindow; }
// QT_END_NAMESPACE

// class MainWindow : public QMainWindow
// {
//     Q_OBJECT

// public:
//     explicit MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();

// private:
//     // --- UI Elements ---
//     QAction *saveAction = nullptr;
//     QAction *exitAction = nullptr;
//     QAction *addAction = nullptr;
//     QAction *deleteAction = nullptr;

//     QTableWidget *table = nullptr;
//     QLabel *incomeLabel = nullptr;
//     QLabel *expenseLabel = nullptr;
//     QLabel *balanceLabel = nullptr;
//     QDateEdit *filterStartDateEdit = nullptr;
//     QDateEdit *filterEndDateEdit = nullptr;

//     // --- Data Manager ---
//     TransactionManager manager;
//     const QString dataFileName = "finance_data.json";

//     // --- Private Slots (Functions connected to signals) ---
// private slots:
//     void addTransaction();
//     void editTransaction();
//     void deleteTransaction();
//     void applyFilters();
//     void clearFilters();

// private:
//     // Core logic methods
//     void setupUI();
//     void setupMenuBar();
//     void setupStatusBar();
//     void setupFilters(QVBoxLayout *layout);
//     void setupConnections();

//     // Data Update Methods
//     void updateAllViews();
//     void updateTable(const QList<Transaction> &list);
//     void updateSummary();

//     // File I/O
//     void loadData();
//     void saveData();

//     // Utility
//     Transaction getSelectedTransaction() const;

// protected:
//     void closeEvent(QCloseEvent *event) override;
// };

// #endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Core Data Files
#include "transactionmanager.h"
#include "transaction.h"
#include "transactiontablemodel.h"

// Qt UI Headers
#include <QAction>
#include <QTableView>
#include <QLabel>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <stdexcept>
#include <QUuid>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // --- UI Elements ---
    QAction *saveAction = nullptr;
    QAction *exitAction = nullptr;
    QAction *addAction = nullptr;
    QAction *deleteAction = nullptr;

    // NEW: CSV Actions
    QAction *exportCsvAction = nullptr;
    QAction *importCsvAction = nullptr;

    QTableView *table = nullptr;
    QLabel *incomeLabel = nullptr;
    QLabel *expenseLabel = nullptr;
    QLabel *balanceLabel = nullptr;
    QDateEdit *filterStartDateEdit = nullptr;
    QDateEdit *filterEndDateEdit = nullptr;

    // --- Data Manager & Model ---
    TransactionManager manager;
    TransactionTableModel *model = nullptr;
    const QString dataFileName = "finance_data.json";

    // --- Private Slots (Functions connected to signals) ---
private slots:
    void addTransaction();
    void editTransaction();
    void deleteTransaction();
    void applyFilters();
    void clearFilters();

    // NEW: Slots for CSV handling
    void exportCsv();
    void importCsv();

private:
    // Core logic methods
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void setupFilters(QVBoxLayout *layout);
    void setupConnections();

    // Data Update Methods
    void updateAllViews();
    void updateSummary();

    // File I/O
    void loadData();
    void saveData();

    // Utility
    QUuid getSelectedTransactionId() const;

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
