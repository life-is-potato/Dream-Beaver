#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H
#include<QString>

class DataBaseConnection
{
private:
        QString host ;
        QString data_base_name ;
        QString username ;
        QString password ;
public:
     bool createconnect() ;
     DataBaseConnection();

};

#endif


