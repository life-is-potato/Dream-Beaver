#include "databaseconnection.h"
#include <QtSql>

bool DataBaseConnection::connect(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC") ;
    db.setHostName("192.168.1.24");
    db.setDatabaseName("fab_lab");
    db.setUserName("Just_Trying");
    db.setPassword("274988");
    return db.open() ;
}

