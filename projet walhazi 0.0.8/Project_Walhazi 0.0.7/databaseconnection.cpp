#include "databaseconnection.h"
#include <QtSql>

bool DataBaseConnection::connect(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC") ;
    db.setDatabaseName("dreambeaver");
    db.setUserName("mahmoud");
    db.setPassword("mahmoud");
    return db.open() ;
}

