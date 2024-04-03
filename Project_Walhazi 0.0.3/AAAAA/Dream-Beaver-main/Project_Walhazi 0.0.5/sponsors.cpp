#include "sponsors.h"
#include "mainwindow.h"



QStandardItemModel * sponsors::afficher() {

    int rows ;
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(5);
    model->setHeaderData(0,Qt::Horizontal,"ID") ;
    model->setHeaderData(1,Qt::Horizontal,"Name") ;
    model->setHeaderData(2,Qt::Horizontal,"Email") ;
    model->setHeaderData(3,Qt::Horizontal,"Number") ;
    model->setHeaderData(4,Qt::Horizontal,"Type") ;

    //l query mta walhezi  :
    QSqlQuery query ;
    query.exec("SELECT * FROM SPONSORES ") ;

    while (query.next()) {
        rows = model->rowCount() ;
        model->insertRow(rows) ;
        for(int i = 0 ; i < 5 ; i++ ){
             model->setData(model->index(rows,i),query.value(i).toString());
       }
    }
    return model ;
}


bool sponsors::Add_element(int id , QString name , QString email , int number , QString type) {

    QSqlQuery q ;

    q.prepare("INSERT INTO SPONSORES(ID,NOM,EMAIL,NUMERO,TYPE) VALUES(:v1,:v2,:v3,:v4,:v5) ") ;
    q.bindValue(":v1",id) ;
    q.bindValue(":v2",name) ;
    q.bindValue(":v3",email) ;
    q.bindValue(":v4",number) ;
    q.bindValue(":v5",type) ;
    return q.exec() ;
}


bool sponsors::Modify_element(int id , QString name , QString email , int number , QString type) {

    QSqlQuery q ;
    q.prepare("UPDATE SPONSORES SET  NOM = :v2, EMAIL =:v3 , NUMERO = :v4, TYPE = :v5 WHERE ID = :v1" ) ;
    q.bindValue(":v1",id) ;
    q.bindValue(":v2",name) ;
    q.bindValue(":v3",email) ;
    q.bindValue(":v4",number) ;
    q.bindValue(":v5",type) ;
    return q.exec() ;


}

bool sponsors::Delete_element(int x ) {
      QSqlQuery q ;
      q.prepare("DELETE FROM SPONSORES WHERE ID = :id ") ;
      q.bindValue(":id",x) ;
      return q.exec() ;
}


sponsors::sponsors()
{

}
