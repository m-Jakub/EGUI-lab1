// databasemanager.h

#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QDateTime>

class DatabaseManager
{
public:
    DatabaseManager(const QString& path);

    // Methods for performing database operations
    int addEmployee(const QString& name, double hourlyRate); // Returns the ID of the newly added employee
    bool removeEmployee(int employeeID);
    bool removeAllEmployees();
    int addCalendarEntry(int employeeID, const QDateTime& startTime, const QDateTime& endTime, const QString& status, const QString& description);
    int addTicket(const QString& vehicleBrand, const QString& vehicleModel, const QString& registrationID, const QString& problemDescription, int assignedEmployeeID, double pricePaidByClient, const QString& state);
    int addRepairSchedule(int ticketID, int employeeID, const QDateTime& startTime, const QDateTime& endTime);
    int addEstimate(int ticketID, const QString& description, double expectedCost, bool acceptedByClient);
    int addParts(int ticketID, const QString& description, double amount, double unitPrice);
    int addWorkLogEntry(int ticketID, int employeeID, const QDateTime& startTime, const QDateTime& endTime);

private:
    QSqlDatabase m_db;
    QString m_path;

    // Helper methods
    bool open();
    void close();
    bool createTables();
};

#endif // DATABASE_MANAGER_H
