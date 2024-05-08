#include "databaseconnection.h"
#include <QtSql>

bool DataBaseConnection::connect(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC") ;
    db.setDatabaseName("Project2A");
    db.setUserName("tpoac");
    db.setPassword("1234");
    return db.open() ;
}

