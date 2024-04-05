#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employees.h"
// class Employees;
#include "tickets.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_Exit_clicked();

    void on_Employees_clicked();

    void on_Tickets_clicked();

private:
    Ui::MainWindow *ui;
    Employees *employeesWindow = nullptr;
    Tickets *ticketsWindow = nullptr;
};
#endif // MAINWINDOW_H
