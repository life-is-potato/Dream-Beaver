#ifndef FORMATION_H
#define FORMATION_H

#include<QString>
#include<QDate>
#include <QMainWindow>
#include <QStandardItemModel>

class formation
{
private:
     int id ;
     int type ;
     QString instructor ;
     QDate dd ;
     QDate df ;
     int num_participants ;
     QString desc ;

public:
     formation();

     int get_id () {
        return id ;
     }
     int get_type() {
        return type ;
     }
     QString get_instructor() {
        return instructor ;
     }
     QDate get_dd() {
        return dd;
     }
     QDate get_df() {
        return df ;
     }
     int get_num_participants() {
        return num_participants ;
     }
     QString get_desc() {
        return desc ;
     }

     void set_id(int x ) {
        id = x ;
     }
     void set_type(int x ) {
        type = x ;
    }
     void set_instructor(QString str ) {
            instructor = str ;
     }
     void set_dd(QDate date ){
        dd = date ;
     }
     void set_df(QDate date) {
            df = date ;
     }
     void set_num_participants(int x ) {
        num_participants = x ;
     }
     void set_desc(QString str ) {
        desc = str ;
     }

     QStandardItemModel * afficher() ;
     bool Add_element(int , int , QString , QString , QString, int , QString ) ;
     bool Modify_element(int , int , QString , QString ,QString, int , QString ) ;
     bool Delete_element(int) ;
};

#endif // FORMATION_H
