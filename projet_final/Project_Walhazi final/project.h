#ifndef PROJECT_H
#define PROJECT_H

#include<QString>
#include <QMainWindow>
#include <QStandardItemModel>

class project
{
private :
     int id ;
     QString name ;
     float budget ;
     int client ;
public:
    project();

    int get_id() {
        return id ;
    }
    QString get_name() {
        return name ;
    }
    float get_budget() {
        return budget ;
    }
    int get_client() {
        return client ;
    }

    void set_id(int x ){
        id = x ;
    }
    void set_name(QString str ) {
        name = str ;
    }
    void set_budget(float f ){
        budget = f ;
    }
    void set_client(int x ) {
        client = x ;
    }

    QStandardItemModel * afficher() ;
    bool Add_element(int , QString , float , int , QString , QString logoFilePath, QString maquetteFilePath) ;
    bool addImageToDatabase(int projectId, QString filePath, QString columnName);
    bool Modify_element(int , QString , float, int , QString ) ;
    bool Delete_element(int) ;
};

#endif // PROJECT_H
