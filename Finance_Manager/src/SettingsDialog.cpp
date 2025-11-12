#include "include/SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(int userId, QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingsDialog), m_userId(userId)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
