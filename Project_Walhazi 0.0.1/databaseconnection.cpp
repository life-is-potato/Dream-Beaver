#include "databaseconnection.h"
#include <QtSql>

DataBaseConnection::DataBaseConnection() {
    // Constructor body
}
bool DataBaseConnection::createconnect()

{bool test=false;

QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

db.setDatabaseName("Source_Projet2A6");

db.setUserName("fatma");//inserer nom de l'utilisateur

db.setPassword("fatma");//inserer mot de passe de cet utilisateur



if (db.open())

test=true;











   return  test;

}
