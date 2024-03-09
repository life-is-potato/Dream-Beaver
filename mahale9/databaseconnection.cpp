#include "databaseconnection.h"
#include <QtSql>


bool DataBaseConnection::connect(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC") ;
    db.setDatabaseName("test-bd");
    db.setUserName("Lehnin");
    db.setPassword("Lehnin123");
    return db.open() ;
}

