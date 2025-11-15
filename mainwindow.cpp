// #include "mainwindow.h"
// #include "transactiondialog.h" // Needed for the dialog windows
// #include "transactionmanager.h"
// #include "transaction.h"
// #include <stdexcept>

// // --- Necessary Qt Widget Includes ---
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QGridLayout>
// #include <QPushButton>
// #include <QHeaderView>
// #include <QMessageBox>
// #include <QCloseEvent>
// #include <QFrame>
// #include <QMenuBar>
// #include <QMenu>
// #include <QAction>
// #include <QStatusBar>
// #include <QSplitter>
// #include <QLabel>
// #include <QTableWidget>
// #include <QDateEdit>
// #include <QTableWidgetItem>
// #include <QAbstractItemView>
// #include <QApplication> // For QKeySequence
// #include <QDebug> // Useful for debugging

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
// {
//     setupUI();
//     setupConnections();

//     loadData();     // Load saved data
//     clearFilters(); // Display data (calls updateAllViews)
// }

// MainWindow::~MainWindow() {}

// void MainWindow::setupUI()
// {
//     setWindowTitle("Personal Finance Manager");
//     setMinimumSize(1200, 800);

//     // Style Sheet (Basic colors for dark theme)
//     setStyleSheet(R"(
//         QWidget {
//             background-color: #2c3e50;
//             color: #ecf0f1;
//             font-family: 'Segoe UI', 'Arial', sans-serif;
//             font-size: 14px;
//         }
//         QFrame#card, QFrame#filterCard {
//             background-color: #34495e;
//             border-radius: 10px;
//             padding: 20px;
//         }
//         QPushButton {
//             background-color: #1abc9c;
//             color: white;
//             border-radius: 8px;
//             padding: 10px 15px;
//             font-weight: bold;
//         }
//         QPushButton#deleteButton { background-color: #e74c3c; }
//         QLabel#incomeLabel { color: #2ecc71; font-size: 18px; }
//         QLabel#expenseLabel { color: #e74c3c; font-size: 18px; }
//     )");

//     setupMenuBar();
//     setupStatusBar();

//     QWidget *central = new QWidget(this);
//     setCentralWidget(central);

//     QHBoxLayout *mainLayout = new QHBoxLayout(central);
//     mainLayout->setSpacing(20);
//     mainLayout->setContentsMargins(20, 20, 20, 20);

//     // --- Left Panel (Filters only) ---
//     QVBoxLayout *leftLayout = new QVBoxLayout();
//     leftLayout->setSpacing(15);
//     setupFilters(leftLayout);

//     // Placeholder for where the chart was (to maintain split structure)
//     QFrame *chartPlaceholder = new QFrame();
//     chartPlaceholder->setStyleSheet("background-color: #34495e; border-radius: 10px;");
//     QLabel *placeholderLabel = new QLabel("Finance Chart Disabled\n(Build error workaround)");
//     placeholderLabel->setAlignment(Qt::AlignCenter);
//     QVBoxLayout *placeholderLayout = new QVBoxLayout(chartPlaceholder);
//     placeholderLayout->addWidget(placeholderLabel);

//     leftLayout->addWidget(chartPlaceholder, 1);

//     // --- Right Panel (Table & Summary) ---
//     QVBoxLayout *rightLayout = new QVBoxLayout();
//     rightLayout->setSpacing(15);

//     // Table setup
//     table = new QTableWidget(0, 5, this);
//     table->setHorizontalHeaderLabels({"Type", "Category", "Amount ($)", "Date", "Note"});
//     table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//     table->setSelectionBehavior(QAbstractItemView::SelectRows);
//     table->setEditTriggers(QAbstractItemView::NoEditTriggers);

//     // Delete Button setup
//     QPushButton *deleteBtn = new QPushButton("Delete Selected Transaction");
//     deleteBtn->setObjectName("deleteButton");
//     QObject::connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteTransaction);

//     // Summary labels setup
//     QHBoxLayout *summaryLayout = new QHBoxLayout();
//     incomeLabel = new QLabel("Total Income: $0.00");
//     incomeLabel->setObjectName("incomeLabel");
//     expenseLabel = new QLabel("Total Expense: $0.00");
//     expenseLabel->setObjectName("expenseLabel");
//     balanceLabel = new QLabel("Total Balance: $0.00");
//     balanceLabel->setObjectName("balanceLabel");

//     summaryLayout->addStretch();
//     summaryLayout->addWidget(incomeLabel);
//     summaryLayout->addSpacing(30);
//     summaryLayout->addWidget(expenseLabel);
//     summaryLayout->addSpacing(30);
//     summaryLayout->addWidget(balanceLabel);
//     summaryLayout->addStretch();

//     rightLayout->addWidget(table, 1);
//     rightLayout->addWidget(deleteBtn);
//     rightLayout->addLayout(summaryLayout);

//     // --- QSplitter (Allows resizing of the two main panels) ---
//     QSplitter *splitter = new QSplitter(Qt::Horizontal);
//     QWidget *leftWidget = new QWidget;
//     leftWidget->setLayout(leftLayout);
//     QWidget *rightWidget = new QWidget;
//     rightWidget->setLayout(rightLayout);
//     splitter->addWidget(leftWidget);
//     splitter->addWidget(rightWidget);
//     splitter->setStretchFactor(0, 1);
//     splitter->setStretchFactor(1, 2);
//     mainLayout->addWidget(splitter);
// }

// void MainWindow::setupMenuBar()
// {
//     QMenu *fileMenu = menuBar()->addMenu("&File");
//     saveAction = fileMenu->addAction("&Save");
//     saveAction->setShortcut(QKeySequence::Save);
//     fileMenu->addSeparator();
//     exitAction = fileMenu->addAction("E&xit");
//     exitAction->setShortcut(QKeySequence::Quit);

//     QMenu *editMenu = menuBar()->addMenu("&Edit");
//     addAction = editMenu->addAction("&Add Transaction...");
//     addAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
//     deleteAction = editMenu->addAction("&Delete Selected");
//     deleteAction->setShortcut(QKeySequence::Delete);
// }

// void MainWindow::setupStatusBar()
// {
//     setStatusBar(new QStatusBar(this));
//     statusBar()->showMessage("Welcome to your Personal Finance Manager!");
// }

// void MainWindow::setupFilters(QVBoxLayout *layout)
// {
//     QFrame *filterCard = new QFrame();
//     filterCard->setObjectName("filterCard");
//     QGridLayout *filterLayout = new QGridLayout(filterCard);
//     filterLayout->setSpacing(10);

//     filterStartDateEdit = new QDateEdit(QDate(QDate::currentDate().year(), 1, 1));
//     filterStartDateEdit->setCalendarPopup(true);
//     filterEndDateEdit = new QDateEdit(QDate::currentDate());
//     filterEndDateEdit->setCalendarPopup(true);

//     QPushButton *filterBtn = new QPushButton("Apply Filter");
//     QPushButton *clearBtn = new QPushButton("Clear Filter");

//     filterLayout->addWidget(new QLabel("From:"), 0, 0);
//     filterLayout->addWidget(filterStartDateEdit, 0, 1);
//     filterLayout->addWidget(new QLabel("To:"), 1, 0);
//     filterLayout->addWidget(filterEndDateEdit, 1, 1);
//     filterLayout->addWidget(filterBtn, 2, 0, 1, 2);
//     filterLayout->addWidget(clearBtn, 3, 0, 1, 2);

//     layout->addWidget(filterCard);

//     QObject::connect(filterBtn, &QPushButton::clicked, this, &MainWindow::applyFilters);
//     QObject::connect(clearBtn, &QPushButton::clicked, this, &MainWindow::clearFilters);
// }

// void MainWindow::setupConnections()
// {
//     QObject::connect(saveAction, &QAction::triggered, this, &MainWindow::saveData);
//     QObject::connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
//     QObject::connect(addAction, &QAction::triggered, this, &MainWindow::addTransaction);
//     QObject::connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteTransaction);
//     QObject::connect(table, &QTableWidget::cellDoubleClicked, this, &MainWindow::editTransaction);
// }

// // --- CORE FEATURES: ADD, EDIT, DELETE ---

// void MainWindow::addTransaction()
// {
//     TransactionDialog dialog(this);
//     // Get all categories for dropdowns
//     QStringList incomeCats = manager.getAllCategories("Income");
//     QStringList expenseCats = manager.getAllCategories("Expense");
//     dialog.setCategoryList(incomeCats + expenseCats);

//     if (dialog.exec() == QDialog::Accepted)
//     {
//         Transaction t = dialog.getTransaction();
//         if (t.category.isEmpty() || t.amount <= 0) {
//             QMessageBox::warning(this, "Invalid Input", "Please enter a valid category and a positive amount.");
//             return;
//         }

//         manager.addTransaction(t);
//         updateAllViews();
//         statusBar()->showMessage("Transaction added successfully.", 2000);
//     }
// }

// void MainWindow::editTransaction()
// {
//     Transaction originalTransaction;
//     try {
//         originalTransaction = getSelectedTransaction();
//     } catch (const std::runtime_error &e) {
//         QMessageBox::warning(this, "No Selection", "Please select a transaction to edit.");
//         return;
//     }

//     TransactionDialog dialog(this);
//     dialog.setTransaction(originalTransaction);
//     dialog.setCategoryList(manager.getAllCategories(originalTransaction.type));

//     if (dialog.exec() == QDialog::Accepted)
//     {
//         Transaction updatedTransaction = dialog.getTransaction();

//         if (updatedTransaction.category.isEmpty() || updatedTransaction.amount <= 0) {
//             QMessageBox::warning(this, "Invalid Input", "Please enter a valid category and a positive amount.");
//             return;
//         }

//         manager.updateTransaction(originalTransaction, updatedTransaction);
//         updateAllViews();
//         statusBar()->showMessage("Transaction updated successfully.", 2000);
//     }
// }

// void MainWindow::deleteTransaction()
// {
//     Transaction t;
//     try {
//         t = getSelectedTransaction();
//     } catch (const std::runtime_error &e) {
//         QMessageBox::warning(this, "No Selection", "Please select a transaction to delete.");
//         return;
//     }

//     QMessageBox::StandardButton reply;
//     reply = QMessageBox::question(this, "Confirm Delete",
//                                   "Are you sure you want to delete this transaction?",
//                                   QMessageBox::Yes | QMessageBox::No);

//     if (reply == QMessageBox::Yes) {
//         manager.removeTransaction(t);
//         updateAllViews();
//         statusBar()->showMessage("Transaction deleted.", 2000);
//     }
// }

// Transaction MainWindow::getSelectedTransaction() const
// {
//     int row = table->currentRow();
//     if (row < 0) {
//         throw std::runtime_error("No row selected");
//     }

//     // Safely extract data from the table row
//     QString type = table->item(row, 0)->text();
//     QString category = table->item(row, 1)->text();
//     // Remove '$' and convert to double
//     double amount = table->item(row, 2)->text().replace('$', ' ').trimmed().toDouble();
//     QDate date = QDate::fromString(table->item(row, 3)->text(), "dd-MM-yyyy");
//     QString note = table->item(row, 4)->text();

//     return Transaction(type, category, amount, date, note);
// }

// // --- FILTERING AND DISPLAY ---

// void MainWindow::applyFilters()
// {
//     updateAllViews();
// }

// void MainWindow::clearFilters()
// {
//     // Reset dates to current year start to current date
//     filterStartDateEdit->setDate(QDate(QDate::currentDate().year(), 1, 1));
//     filterEndDateEdit->setDate(QDate::currentDate());
//     updateAllViews();
// }

// void MainWindow::updateAllViews()
// {
//     manager.sortByDate(); // Ensure data is sorted

//     QDate start = filterStartDateEdit->date();
//     QDate end = filterEndDateEdit->date();
//     QList<Transaction> filteredList = manager.getFilteredTransactions(start, end);

//     updateTable(filteredList);
//     updateSummary();
// }

// void MainWindow::updateTable(const QList<Transaction> &list)
// {
//     table->setRowCount(0);

//     for (const auto &t : list) {
//         int row = table->rowCount();
//         table->insertRow(row);

//         QTableWidgetItem *typeItem = new QTableWidgetItem(t.type);
//         QTableWidgetItem *amountItem = new QTableWidgetItem(QString("$%1").arg(t.amount, 0, 'f', 2));

//         // Color code amounts based on type
//         if (t.type == "Income") {
//             amountItem->setForeground(QColor("#2ecc71"));
//         } else {
//             amountItem->setForeground(QColor("#e74c3c"));
//         }

//         table->setItem(row, 0, typeItem);
//         table->setItem(row, 1, new QTableWidgetItem(t.category));
//         table->setItem(row, 2, amountItem);
//         table->setItem(row, 3, new QTableWidgetItem(t.date.toString("dd-MM-yyyy")));
//         table->setItem(row, 4, new QTableWidgetItem(t.note));
//     }
// }

// void MainWindow::updateSummary()
// {
//     double income = manager.getTotalIncome();
//     double expense = manager.getTotalExpense();
//     double balance = manager.getBalance();

//     incomeLabel->setText(QString("Total Income: $%1").arg(income, 0, 'f', 2));
//     expenseLabel->setText(QString("Total Expense: $%1").arg(expense, 0, 'f', 2));
//     balanceLabel->setText(QString("Total Balance: $%1").arg(balance, 0, 'f', 2));

//     // Conditional styling for balance label
//     balanceLabel->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: bold;");

//     if (balance < 0) {
//         balanceLabel->setStyleSheet("color: #e74c3c; font-size: 18px; font-weight: bold;");
//     } else if (balance > 0) {
//         balanceLabel->setStyleSheet("color: #2ecc71; font-size: 18px; font-weight: bold;");
//     }
// }

// // --- FILE I/O ---

// void MainWindow::loadData()
// {
//     if (manager.loadFromFile(dataFileName)) {
//         statusBar()->showMessage("Data loaded from " + dataFileName, 2000);
//     } else {
//         statusBar()->showMessage("No existing data file found. Starting fresh.", 2000);
//     }
// }

// void MainWindow::saveData()
// {
//     if (manager.saveToFile(dataFileName)) {
//         statusBar()->showMessage("Data saved to " + dataFileName, 2000);
//     } else {
//         statusBar()->showMessage("Error saving data.", 2000);
//     }
// }

// void MainWindow::closeEvent(QCloseEvent *event)
// {
//     saveData();
//     event->accept();
// }


#include "mainwindow.h"
#include "transactiondialog.h"
#include "transactiontablemodel.h"
#include <stdexcept>

// --- Necessary Qt Widget Includes ---
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFrame>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QSplitter>
#include <QLabel>
#include <QTableView> // CHANGE: QTableView
#include <QDateEdit>
#include <QAbstractItemView>
#include <QApplication>
#include <QDebug>
#include <QFileDialog> // NEW: For file dialogs

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupConnections();

    loadData();     // Load saved data
    clearFilters(); // Display data (calls updateAllViews)
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    setWindowTitle("Personal Finance Manager");
    setMinimumSize(1200, 800);

    // Style Sheet (Basic colors for dark theme)
    setStyleSheet(R"(
        QWidget {
            background-color: #2c3e50;
            color: #ecf0f1;
            font-family: 'Segoe UI', 'Arial', sans-serif;
            font-size: 14px;
        }
        QFrame#card, QFrame#filterCard {
            background-color: #34495e;
            border-radius: 10px;
            padding: 20px;
        }
        QPushButton {
            background-color: #1abc9c;
            color: white;
            border-radius: 8px;
            padding: 10px 15px;
            font-weight: bold;
        }
        QPushButton:hover { background-color: #16a085; }
        QPushButton#deleteButton { background-color: #e74c3c; }
        QLabel#incomeLabel { color: #2ecc71; font-size: 18px; }
        QLabel#expenseLabel { color: #e74c3c; font-size: 18px; }
        QTableView {
            gridline-color: #34495e;
            background-color: #2c3e50;
            alternate-background-color: #34495e;
        }
    )");

    setupMenuBar();
    setupStatusBar();

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // --- Left Panel (Filters and Chart Placeholder) ---
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->setSpacing(15);
    setupFilters(leftLayout);

    QFrame *chartPlaceholder = new QFrame();
    chartPlaceholder->setStyleSheet("background-color: #34495e; border-radius: 10px;");
    QLabel *placeholderLabel = new QLabel("Finance Chart Placeholder");
    placeholderLabel->setAlignment(Qt::AlignCenter);
    QVBoxLayout *placeholderLayout = new QVBoxLayout(chartPlaceholder);
    placeholderLayout->addWidget(placeholderLabel);

    leftLayout->addWidget(chartPlaceholder, 1);

    // --- Right Panel (Table & Summary) ---
    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(15);

    // Model setup
    model = new TransactionTableModel(&manager, this);

    // Table setup (View)
    table = new QTableView(this); // CHANGE: QTableView
    table->setModel(model); // Link the Model to the View
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);

    // Delete Button setup
    QPushButton *deleteBtn = new QPushButton("Delete Selected Transaction");
    deleteBtn->setObjectName("deleteButton");
    QObject::connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteTransaction);

    // Summary labels setup
    QHBoxLayout *summaryLayout = new QHBoxLayout();
    incomeLabel = new QLabel("Total Income: $0.00");
    incomeLabel->setObjectName("incomeLabel");
    expenseLabel = new QLabel("Total Expense: $0.00");
    expenseLabel->setObjectName("expenseLabel");
    balanceLabel = new QLabel("Total Balance: $0.00");
    balanceLabel->setObjectName("balanceLabel");

    summaryLayout->addStretch();
    summaryLayout->addWidget(incomeLabel);
    summaryLayout->addSpacing(30);
    summaryLayout->addWidget(expenseLabel);
    summaryLayout->addSpacing(30);
    summaryLayout->addWidget(balanceLabel);
    summaryLayout->addStretch();

    rightLayout->addWidget(table, 1);
    rightLayout->addWidget(deleteBtn);
    rightLayout->addLayout(summaryLayout);

    // --- QSplitter (Allows resizing of the two main panels) ---
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    QWidget *leftWidget = new QWidget;
    leftWidget->setLayout(leftLayout);
    QWidget *rightWidget = new QWidget;
    rightWidget->setLayout(rightLayout);
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);
    mainLayout->addWidget(splitter);
}

void MainWindow::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu("&File");

    // NEW: CSV Actions
    exportCsvAction = fileMenu->addAction("&Export to CSV...");
    importCsvAction = fileMenu->addAction("&Import from CSV...");

    fileMenu->addSeparator();

    saveAction = fileMenu->addAction("&Save");
    saveAction->setShortcut(QKeySequence::Save);
    fileMenu->addSeparator();

    exitAction = fileMenu->addAction("E&xit");
    exitAction->setShortcut(QKeySequence::Quit);

    QMenu *editMenu = menuBar()->addMenu("&Edit");
    addAction = editMenu->addAction("&Add Transaction...");
    addAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    deleteAction = editMenu->addAction("&Delete Selected");
    deleteAction->setShortcut(QKeySequence::Delete);
}

void MainWindow::setupStatusBar()
{
    setStatusBar(new QStatusBar(this));
    statusBar()->showMessage("Welcome to your Personal Finance Manager!");
}

void MainWindow::setupFilters(QVBoxLayout *layout)
{
    QFrame *filterCard = new QFrame();
    filterCard->setObjectName("filterCard");
    QGridLayout *filterLayout = new QGridLayout(filterCard);
    filterLayout->setSpacing(10);

    filterStartDateEdit = new QDateEdit(QDate(QDate::currentDate().year(), 1, 1));
    filterStartDateEdit->setCalendarPopup(true);
    filterEndDateEdit = new QDateEdit(QDate::currentDate());
    filterEndDateEdit->setCalendarPopup(true);

    QPushButton *filterBtn = new QPushButton("Apply Filter");
    QPushButton *clearBtn = new QPushButton("Clear Filter");

    filterLayout->addWidget(new QLabel("From:"), 0, 0);
    filterLayout->addWidget(filterStartDateEdit, 0, 1);
    filterLayout->addWidget(new QLabel("To:"), 1, 0);
    filterLayout->addWidget(filterEndDateEdit, 1, 1);
    filterLayout->addWidget(filterBtn, 2, 0, 1, 2);
    filterLayout->addWidget(clearBtn, 3, 0, 1, 2);

    layout->addWidget(filterCard);

    QObject::connect(filterBtn, &QPushButton::clicked, this, &MainWindow::applyFilters);
    QObject::connect(clearBtn, &QPushButton::clicked, this, &MainWindow::clearFilters);
}

void MainWindow::setupConnections()
{
    QObject::connect(saveAction, &QAction::triggered, this, &MainWindow::saveData);
    QObject::connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    // NEW: Connect CSV actions
    QObject::connect(exportCsvAction, &QAction::triggered, this, &MainWindow::exportCsv);
    QObject::connect(importCsvAction, &QAction::triggered, this, &MainWindow::importCsv);

    QObject::connect(addAction, &QAction::triggered, this, &MainWindow::addTransaction);
    QObject::connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteTransaction);
    QObject::connect(table, &QTableView::doubleClicked, this, &MainWindow::editTransaction);
}

// --- CORE FEATURES: ADD, EDIT, DELETE ---

void MainWindow::addTransaction()
{
    TransactionDialog dialog(this);
    QStringList incomeCats = manager.getAllCategories("Income");
    QStringList expenseCats = manager.getAllCategories("Expense");
    dialog.setCategoryList(incomeCats + expenseCats);

    if (dialog.exec() == QDialog::Accepted)
    {
        Transaction t = dialog.getTransaction();
        if (t.category.isEmpty() || t.amount <= 0) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid category and a positive amount.");
            return;
        }

        manager.addTransaction(t);
        updateAllViews();
        statusBar()->showMessage("Transaction added successfully.", 2000);
    }
}

void MainWindow::editTransaction()
{
    QUuid idToEdit;
    try {
        idToEdit = getSelectedTransactionId();
    } catch (const std::runtime_error &e) {
        QMessageBox::warning(this, "No Selection", "Please select a transaction to edit.");
        return;
    }

    // Retrieve the full original transaction using the ID
    Transaction originalTransaction = manager.getTransactionById(idToEdit);

    TransactionDialog dialog(this);
    dialog.setTransaction(originalTransaction);
    dialog.setCategoryList(manager.getAllCategories(originalTransaction.type));

    if (dialog.exec() == QDialog::Accepted)
    {
        Transaction updatedTransaction = dialog.getTransaction();

        if (updatedTransaction.category.isEmpty() || updatedTransaction.amount <= 0) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid category and a positive amount.");
            return;
        }

        // Pass the original ID and the updated data to the manager
        manager.updateTransaction(idToEdit, updatedTransaction);
        updateAllViews();
        statusBar()->showMessage("Transaction updated successfully.", 2000);
    }
}

void MainWindow::deleteTransaction()
{
    QUuid idToDelete;
    try {
        idToDelete = getSelectedTransactionId();
    } catch (const std::runtime_error &e) {
        QMessageBox::warning(this, "No Selection", "Please select a transaction to delete.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete",
                                  "Are you sure you want to delete this transaction?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Delete using the unique ID
        manager.removeTransaction(idToDelete);
        updateAllViews();
        statusBar()->showMessage("Transaction deleted.", 2000);
    }
}

QUuid MainWindow::getSelectedTransactionId() const
{
    QModelIndexList selectedIndexes = table->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        throw std::runtime_error("No row selected");
    }

    // The index points to the row (and column 0)
    QModelIndex firstSelectedIndex = selectedIndexes.first();
    int row = firstSelectedIndex.row();

    // Use the model to retrieve the hidden ID for that row
    return model->getId(row);
}

// --- FILTERING AND DISPLAY ---

void MainWindow::applyFilters()
{
    updateAllViews();
}

void MainWindow::clearFilters()
{
    filterStartDateEdit->setDate(QDate(QDate::currentDate().year(), 1, 1));
    filterEndDateEdit->setDate(QDate::currentDate());
    updateAllViews();
}

void MainWindow::updateAllViews()
{
    manager.sortByDate();

    QDate start = filterStartDateEdit->date();
    QDate end = filterEndDateEdit->date();
    QList<Transaction> filteredList = manager.getFilteredTransactions(start, end);

    // CHANGE: Update the Model, not the table directly
    model->setTransactions(filteredList);

    updateSummary();
}

void MainWindow::updateSummary()
{
    double income = manager.getTotalIncome();
    double expense = manager.getTotalExpense();
    double balance = manager.getBalance();

    incomeLabel->setText(QString("Total Income: $%1").arg(income, 0, 'f', 2));
    expenseLabel->setText(QString("Total Expense: $%1").arg(expense, 0, 'f', 2));
    balanceLabel->setText(QString("Total Balance: $%1").arg(balance, 0, 'f', 2));

    // Conditional styling for balance label
    balanceLabel->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: bold;");

    if (balance < 0) {
        balanceLabel->setStyleSheet("color: #e74c3c; font-size: 18px; font-weight: bold;");
    } else if (balance > 0) {
        balanceLabel->setStyleSheet("color: #2ecc71; font-size: 18px; font-weight: bold;");
    }
}

// --- NEW: CSV Import/Export Methods ---

void MainWindow::exportCsv()
{
    QString defaultPath = QDir::homePath() + "/finance_export.csv";
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Export Transactions to CSV",
                                                    defaultPath,
                                                    "CSV Files (*.csv);;All Files (*)");

    if (!fileName.isEmpty()) {
        if (manager.exportToCsv(fileName)) {
            statusBar()->showMessage("Data successfully exported to CSV.", 3000);
        } else {
            QMessageBox::critical(this, "Export Error", "Failed to save data to the specified CSV file.");
            statusBar()->showMessage("CSV export failed.", 3000);
        }
    }
}

void MainWindow::importCsv()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Import Transactions from CSV",
                                                    QDir::homePath(),
                                                    "CSV Files (*.csv);;All Files (*)");

    if (!fileName.isEmpty()) {
        if (manager.importFromCsv(fileName)) {
            updateAllViews(); // Refresh the table with new imported data
            saveData();       // Automatically save the changes to the JSON file
            statusBar()->showMessage("Data successfully imported from CSV. Changes saved.", 5000);
        } else {
            QMessageBox::warning(this, "Import Warning", "Failed to import transactions. Check if the file format is correct and try again.");
            statusBar()->showMessage("CSV import failed.", 3000);
        }
    }
}

// --- FILE I/O ---

void MainWindow::loadData()
{
    if (manager.loadFromFile(dataFileName)) {
        statusBar()->showMessage("Data loaded from " + dataFileName, 2000);
    } else {
        statusBar()->showMessage("No existing data file found. Starting fresh.", 2000);
    }
}

void MainWindow::saveData()
{
    if (manager.saveToFile(dataFileName)) {
        statusBar()->showMessage("Data saved to " + dataFileName, 2000);
    } else {
        statusBar()->showMessage("Error saving data.", 2000);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveData();
    event->accept();
}
