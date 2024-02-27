#include "connection.h"
#include <QDebug>

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
       return false  ;
    } else {
        return true ;
    }
}
