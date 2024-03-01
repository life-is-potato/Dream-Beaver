#ifndef COSTUMER_H
#define COSTUMER_H
#include <iostream>
#include <string>
using namespace std;
#include<QString>
#include <QMainWindow>
#include <QStandardItemModel>
#include<qdebug.h>
#include "connection.h"
#include <QDate>

class Costumer
{
    int cin=0;
    QDate dOb;
    int number=0;
    QString fName;
    QString lName;
    QString email;
   public:
    Costumer();

    int getCin();
    QDate getDoB();
    int getNumber();
    QString getFname();
    QString getLname();
    QString getEmail();

    void setCin(int nvCin);
    void setDoB(QDate nvDoB);
    void setFname(QString nvFname);
    void setLname(QString nvLname);
    void setEmail(QString nvEmail);

    bool AjouterClient(int cinnv,QDate nvdob,int nvnumber,QString nvfName, QString nvlName , QString nvemail );
    QStandardItemModel* afficher();
    bool EffacerClient(int n);
    bool Modify_element(int cinnv,QDate nvdob,int nvnumber,QString nvfName,QString nvlName,QString nvemail);

};

#endif // COSTUMER_H
