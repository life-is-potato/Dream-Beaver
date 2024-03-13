#include "connection.h"
#include <QDebug>
#include <QMessageBox>
Connection::Connection()
{

}

bool Connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("192.168.1.100");
    db.setDatabaseName("dreambeaver");
    db.setUserName("mahmoud");
    db.setPassword("mahmoud");

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", "Error opening database: " + db.lastError().text());
        return false;
    } else {
        return true;
    }
}
