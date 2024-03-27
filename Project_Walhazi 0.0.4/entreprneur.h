#ifndef ENTREPRNEUR_H
#define ENTREPRNEUR_H

#include<QString>
#include <QMainWindow>
#include <QStandardItemModel>
#include "databaseconnection.h"
#include "QDate"
class entreprneur
{
private:
    int cin ;
    QString nom ;
    QString prenom;
    QDate ddn;
    int numero;
    QString email ;

public:
    entreprneur();
    int get_cin() {
        return cin ;
    }
    QString get_nom() {
        return nom ;
    }
    QString get_prenom() {
        return prenom ;
    }
    QDate get_ddn() {
        return ddn ;
    }
    int get_numero() {
        return numero ;
    }
    QString get_emai() {
        return email ;
    }

    void set_cin(int x ){
        cin = x ;
    }
    void set_nom(QString str ) {
        nom = str;
    }
    void set_prenom(QString str ){
           prenom = str ;
    }

    void set_ddn(QDate date ){
        ddn = date ;
    }

    void set_numero(int x ){
        numero = x ;
    }

    void set_email(QString str) {
        email = str ;
    }

    QStandardItemModel * afficher() ;
    bool Add_element(int cin, QString email, QDate ddn , int numero , QString nom, QString prenom) ;
    bool Modify_element(int cin, QString email, QDate ddn , int numero , QString nom, QString prenom ) ;
    bool Delete_element(int n) ;
    QStandardItemModel* recherche_projet(QString str);
    QString getPoints(QString cin) ;
    QString addPoints(QString cin,int p);
    QString losePoints(QString cin,int p);
    bool addFreeFormation(QString cin,QString idf);
    bool isFormationValid(int formationId);
};

#endif // ENTREPRNEUR_H
