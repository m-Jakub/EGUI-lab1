// add_ticket_dialog.h
#ifndef ADD_TICKET_DIALOG_H
#define ADD_TICKET_DIALOG_H

#include <QDialog>
#include "database_manager.h"
#include "calendar.h"

namespace Ui
{
    class AddTicketDialog;
}

class AddTicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTicketDialog(DatabaseManager *dbManager, const QString &brand = "", const QString &model = "", const QString &problemDescription = "", const QString &registrationID = "", int assignedEmployeeID = 0, bool choose_employee_only = false, int ticketID = 0, QWidget *parent = nullptr);
    ~AddTicketDialog();
    void disableFields(bool disable);
    void fillFields(const QString &brand, const QString &model, const QString &registrationID, const QString &problemDescription, int assignedEmployeeID);

signals:
    void addTicket(const QString &brand, const QString &model, const QString &registrationID, const QString &problemDescription, int assignedEmployeeID, const QString &startHour, const QString &endHour, const QString &day);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void setupTable();
    void populateTable();

private:
    Ui::AddTicketDialog *ui;
    DatabaseManager *dbManager;
    QHash<int, int> rowToIdMap;
    Calendar *calendar = nullptr;
    bool initialized = false;
    bool choose_employee_only;
    int ticketID;
};

#endif // ADD_TICKET_DIALOG_H
