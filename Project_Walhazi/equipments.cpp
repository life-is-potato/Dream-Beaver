#include "equipments.h"
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QtSql>
#include "mainwindow.h"


 QStandardItemModel * Equipments::afficher() {
     int rows ;
     QStandardItemModel * model = new QStandardItemModel();
     model->setColumnCount(5);
     model->setHeaderData(0,Qt::Horizontal,"ID") ;
     model->setHeaderData(1,Qt::Horizontal,"Name") ;
     model->setHeaderData(2,Qt::Horizontal,"Type") ;
     model->setHeaderData(3,Qt::Horizontal,"Quantity") ;
     model->setHeaderData(4,Qt::Horizontal,"Disponibility") ;
     //l query mta walhezi  :
     QSqlQuery query ;
     query.exec("SELECT * FROM EQUIPEMENTS ") ;
     // (query.next()) ==> tt3ada ll query li ba3dha ;

     while (query.next()) {
         rows = model->rowCount() ;
         model->insertRow(rows) ;
         for(int i = 0 ; i < 5 ; i++ ){
              model->setData(model->index(rows,i),query.value(i).toString());
        }
     }
     return model ;
}

 bool Equipments::Add_element(int id , QString name , int type , int qnt , QString disp, QString desc) {
     QSqlQuery q ;
     q.prepare("INSERT INTO EQUIPEMENTS VALUES(:v1,:v2,:v3,:v4,:v5,:v6) ") ;
     q.bindValue(":v1",id) ;
     q.bindValue(":v2",name) ;
     q.bindValue(":v3",type) ;
     q.bindValue(":v4",qnt) ;
     q.bindValue(":v5",disp) ;
     q.bindValue(":v6",desc) ;

     return q.exec() ;

 }

 bool Equipments::Modify_element(int id , QString name , int type , int qnt , QString disp, QString desc) {

     QSqlQuery q ;
     q.prepare("UPDATE EQUIPEMENTS SET  NOM = :v2, TYPE =:v3 , QNT_STOCK = :v4, DISPONIBILITE = :v5, DESCRIPTION = :v6 WHERE ID = :v1 ") ;
     q.bindValue(":v1",id) ;
     q.bindValue(":v2",name) ;
     q.bindValue(":v3",type) ;
     q.bindValue(":v4",qnt) ;
     q.bindValue(":v5",disp) ;
     q.bindValue(":v6",desc) ;
     return q.exec() ;

 }

 bool Equipments::Delete_element(int x ) {
       QSqlQuery q ;
       q.prepare("DELETE FROM EQUIPEMENTS WHERE ID = :id ") ;
       q.bindValue(":id",x) ;
       return q.exec() ;
 }


 QStandardItemModel * Equipments::search_element(QString str)
 {
     int rows;
     QSqlQuery query;
     QStandardItemModel *model = new QStandardItemModel();

     model->setColumnCount(5);
     model->setHeaderData(0, Qt::Horizontal, "ID");
     model->setHeaderData(1, Qt::Horizontal, "Name");
     model->setHeaderData(2, Qt::Horizontal, "Type");
     model->setHeaderData(3, Qt::Horizontal, "Quantity");
     model->setHeaderData(4, Qt::Horizontal, "Disponibility");

     query.prepare("SELECT * FROM EQUIPEMENTS WHERE ID LIKE :x || '%' OR NOM LIKE :x || '%' ");
     query.bindValue(":x", str);
     if (query.exec()) {
         while (query.next()) {
             rows = model->rowCount();
             model->insertRow(rows);
             for (int i = 0; i < 5; i++) {
                 model->setData(model->index(rows, i), query.value(i).toString());
             }
         }
     } else {
         qDebug() << "Query failed:" << query.lastError();
     }
     return model;
 }

 QStandardItemModel * Equipments::tri_by_type() {
     int rows ;
     QStandardItemModel * model = new QStandardItemModel();
     QSqlQuery query ;

     model->setColumnCount(5);
     model->setHeaderData(0,Qt::Horizontal,"ID") ;
     model->setHeaderData(1,Qt::Horizontal,"Name") ;
     model->setHeaderData(2,Qt::Horizontal,"Type") ;
     model->setHeaderData(3,Qt::Horizontal,"Quantity") ;
     model->setHeaderData(4,Qt::Horizontal,"Disponibility") ;

     query.exec("SELECT * FROM EQUIPEMENTS ORDER BY type DESC") ;

     while (query.next()) {
         rows = model->rowCount() ;
         model->insertRow(rows) ;
         for(int i = 0 ; i < 5 ; i++ ){
              model->setData(model->index(rows,i),query.value(i).toString());
        }
     }
     return model ;
 }

 QStandardItemModel * Equipments::tri_by_quantity() {
     int rows ;
     QStandardItemModel * model = new QStandardItemModel();
     QSqlQuery query ;

     model->setColumnCount(5);
     model->setHeaderData(0,Qt::Horizontal,"ID") ;
     model->setHeaderData(1,Qt::Horizontal,"Name") ;
     model->setHeaderData(2,Qt::Horizontal,"Type") ;
     model->setHeaderData(3,Qt::Horizontal,"Quantity") ;
     model->setHeaderData(4,Qt::Horizontal,"Disponibility") ;

     query.exec("SELECT * FROM EQUIPEMENTS ORDER BY QNT_STOCK ASC") ;

     while (query.next()) {
         rows = model->rowCount() ;
         model->insertRow(rows) ;
         for(int i = 0 ; i < 5 ; i++ ){
              model->setData(model->index(rows,i),query.value(i).toString());
        }
     }
     return model ;
 }
