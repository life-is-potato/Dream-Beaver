#ifndef SPONSORS_H
#define SPONSORS_H

#include<QString>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QDate>

class sponsors
{
private :
    int id ;
    QString name ;
    QString email ;
    int number ;
    QString type ;

public:
    int get_id() {
        return id ;
    }
    QString get_name() {
        return name ;
    }
    QString get_email() {
        return  email ;
    }
    int get_number() {
        return number ;
    }
    QString get_type() {
        return type ;
    }

    void set_id(int x ){
        id = x ;
    }

    void set_name(QString str ){
        name = str ;
    }

    void set_email(QString str) {
        email = str ;
    }
    void set_number(int x ){
        number = x ;
    }
    void set_type(QString str) {
        type = str ;
    }
    sponsors();

    QStandardItemModel * afficher() ;
    bool Add_element(int , QString , QString , int , QString) ;
    bool Modify_element(int , QString , QString , int , QString) ;
    bool Delete_element(int) ;
};

#endif // SPONSORS_H
