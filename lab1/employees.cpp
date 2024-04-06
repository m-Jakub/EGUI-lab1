#include "employees.h"
#include "ui_employees.h"
#include "database_manager.h"
#include "delete_confirmation_dialog.h"
#include <QSqlQuery>

Employees::Employees(DatabaseManager *dbManager, QWidget *parent)
    : QWidget(parent), ui(new Ui::Employees), dbManager(dbManager)
{
    ui->setupUi(this);

    setupTable();
    populateTable();
}

void Employees::setupTable()
{
    // Setting column names
    QStringList headerLabels;
    headerLabels << "Name"
                 << "Hourly Rate [$]";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);

    // Resizing columns
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Setting selection behavior to select the whole row
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Setting the window title
    setWindowTitle("Employees");
}

void Employees::populateTable()
{
    QSqlQuery query("SELECT EmployeeId, Name, HourlyRate FROM Employees");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString hourlyRate = query.value(2).toString();

        QTableWidgetItem *nameItem = new QTableWidgetItem(name);
        QTableWidgetItem *rateItem = new QTableWidgetItem(hourlyRate);

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, nameItem);
        ui->tableWidget->setItem(row, 1, rateItem);

        // Storing the ID in the rowToIdMap
        rowToIdMap[row] = id;
    }
}

Employees::~Employees()
{
    delete ui;
}

void Employees::on_Delete_clicked()
{
    int selectedRow = ui->tableWidget->currentRow();

    if (selectedRow >= 0)
    {
        // Retrieving the name using the row index
        QString employeeName = ui->tableWidget->item(selectedRow, 0)->text();

        // Instantiating the DeleteConfirmationDialog with the employee name
        DeleteConfirmationDialog confirmationDialog(employeeName);

        // Connecting the deleteConfirmed() signal to a slot that performs deletion
        // Lambda function is executed when the deleteConfirmed signal is emitted
        connect(&confirmationDialog, &DeleteConfirmationDialog::deleteConfirmed, this, [=]()
                {
            // Retrieve the ID using the row index
            int employeeId = rowToIdMap.value(selectedRow);

            // Removing the employee from the database using the DatabaseManager object
            dbManager->removeEmployee(employeeId);

            // Removing the row from the tableWidget
            ui->tableWidget->removeRow(selectedRow);

            // Removing the ID from the rowToIdMap
            rowToIdMap.remove(selectedRow); });

        // Displaying the confirmation dialog
        confirmationDialog.exec();
    }
}

void Employees::on_Add_clicked()
{
    // Instantiating the AddEmployeeDialog
    addEmployeeWindow = new AddEmployeeDialog(dbManager);

    // Connecting the addEmployee signal to a slot that adds the employee to the table
    connect(addEmployeeWindow, &AddEmployeeDialog::addEmployee, this, [=](const QString &name, double hourlyRate)
            {
        // Inserting the employee into the database
        int id = dbManager->addEmployee(name, hourlyRate);

        // Inserting the employee into the tableWidget
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(hourlyRate)));

        // Storing the ID in the rowToIdMap
        rowToIdMap[row] = id; });

    // Displaying the addEmployeeWindow
    addEmployeeWindow->exec();
}
