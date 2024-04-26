#ifndef EQUIPMENTS_H
#define EQUIPMENTS_H
#include<QString>
#include <QMainWindow>
#include <QStandardItemModel>
#include "databaseconnection.h"
#include "barcodeprinter.h"


class Equipments
{
    private :
        int id ;
        QString name ;
        QString type ;
        long int  bare_code ;

    public:

        // Constructor
        Equipments() ;

        // getters :
        int get_id() {
               return id ;
        }
        QString get_name(){
            return name ;
        }
        QString get_type() {
            return type ;
        }
        long int get_bare_code () {
            return bare_code ;
        }

        //setters

        void set_id (int x ) {
              id = x ;
        }

        void set_name(QString str){
            name = str ;
        }

        void set_type(QString str) {
              type = str ;
        }

        void set_bare_code(long int x ){
            bare_code = x ;
        }


        //functions :

        QStandardItemModel * afficher() ;
        QStandardItemModel * search_element(QString str) ;
        QStandardItemModel * tri_by_type() ;
        QStandardItemModel * tri_by_quantity() ;
        bool read_from_arduino() ;
        bool Add_element(int , QString , int , int , QString , QString ) ;
        bool Modify_element(int , QString , int , int , QString , QString ) ;
        bool Delete_element(int) ;

};

#endif // EQUIPMENTS_H
