#include "include/ReportWindow.h"
#include "ui_ReportWindow.h"

ReportWindow::ReportWindow(int userId, QWidget *parent)
    : QDialog(parent), ui(new Ui::ReportWindow), m_userId(userId)
{
    ui->setupUi(this);
}

ReportWindow::~ReportWindow()
{
    delete ui;
}
