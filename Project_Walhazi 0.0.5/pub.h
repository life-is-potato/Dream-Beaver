#ifndef PUB_H
#define PUB_H

#include<QString>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QDate>

class pub
{
private :
    int id ;
    QString name ;
    int type ;
    float cout ;
    QDate dd ;
    QDate df ;
    int projet_id ;
public:
    int get_id() {
        return id ;
    }
    QString get_name() {
        return name ;
    }
    float get_cout(){
        return cout ;
    }
    QDate get_dd() {
        return dd ;
    }
    QDate get_df() {
        return df ;
    }
    int get_project_id() {
        return projet_id ;
    }

    void set_id(int x)
    {
        id = x ;
    }
    void set_name(QString str){
        name = str ;
    }
    void set_type(int x ){
        type = x ;
    }
    void set_dd(QDate d) {
        dd = d ;
    }
    void set_df(QDate d ) {
        df = d ;
    }
    void set_projet_id(int x ) {
        projet_id = x;
    }
    pub();

    QStandardItemModel * afficher() ;
    bool Add_element(int , QString , int , int , QString , QString ,int ) ;
    bool Modify_element(int , QString , int , int , QString , QString ,int ) ;
    bool Delete_element(int) ;
};

#endif // PUB_H
