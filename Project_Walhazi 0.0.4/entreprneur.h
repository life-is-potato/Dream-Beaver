#ifndef ENTREPRNEUR_H
#define ENTREPRNEUR_H

#include<QString>
#include <QMainWindow>
#include <QStandardItemModel>
#include "databaseconnection.h"
class entreprneur
{
private:
    int cin ;
    QString nom ;
    QString prenom;
    QString ddn;
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
    QString get_ddn() {
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

    void set_ddn(QString date ){
        ddn = date ;
    }

    void set_numero(int x ){
        numero = x ;
    }

    void set_email(QString str) {
        email = str ;
    }

    QStandardItemModel * afficher() ;
    bool Add_element(int , QString , int , int , QString , QString ) ;
    bool Modify_element(int , QString , int , int , QString , QString ) ;
    bool Delete_element(int) ;

};

#endif // ENTREPRNEUR_H
