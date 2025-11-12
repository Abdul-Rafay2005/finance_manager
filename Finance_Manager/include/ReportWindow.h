#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QDialog>

namespace Ui { class ReportWindow; }

class ReportWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ReportWindow(int userId, QWidget *parent = nullptr);
    ~ReportWindow();

private:
    Ui::ReportWindow *ui;
    int m_userId;
};

#endif // REPORTWINDOW_H
