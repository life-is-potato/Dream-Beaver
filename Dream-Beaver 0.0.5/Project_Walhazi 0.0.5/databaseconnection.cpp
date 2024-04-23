#include "databaseconnection.h"
#include <QtSql>

bool DataBaseConnection::connect(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC") ;
    db.setDatabaseName("fab_lab");
    db.setUserName("Jessy");
    db.setPassword("274988");
    return db.open() ;
}

