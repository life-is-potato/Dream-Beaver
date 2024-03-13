#include "entreprneur.h"
#include "mainwindow.h"


QStandardItemModel * entreprneur::afficher() {
    int rows ;
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(5);
    model->setHeaderData(0,Qt::Horizontal,"CIN") ;
    model->setHeaderData(1,Qt::Horizontal,"Name") ;
    model->setHeaderData(2,Qt::Horizontal,"Prenom") ;
    model->setHeaderData(3,Qt::Horizontal,"Dob") ;
    model->setHeaderData(4,Qt::Horizontal,"Numero") ;
    model->setHeaderData(4,Qt::Horizontal,"email") ;

    //l query mta walhezi  :
    QSqlQuery query ;
    query.exec("SELECT * FROM ENTREPRENEURS ") ;
    // (query.next()) ==> tt3ada ll query li ba3dha ;

    while (query.next()) {
        rows = model->rowCount() ;
        model->insertRow(rows) ;
        for(int i = 0 ; i < 6 ; i++ ){
             model->setData(model->index(rows,i),query.value(i).toString());
       }
    }
    return model ;
}

bool entreprneur::Add_element(int cin , QString name , int prenom , int ddn , QString numero, QString email) {

    QSqlQuery q ;

    q.prepare("INSERT INTO ENTREPRENEURS(CIN,NOM,PRENOM,DDN,NUMERO,EMAIL) VALUES(:v1,:v2,:v3,:v4,:v5,:v6) ") ;
    q.bindValue(":v1",cin) ;
    q.bindValue(":v2",name) ;
    q.bindValue(":v3",prenom) ;
    q.bindValue(":v4",ddn) ;
    q.bindValue(":v5",numero) ;
    q.bindValue(":v6",email) ;
    return q.exec() ;

}


bool entreprneur::Modify_element(int cin , QString name , int prenom , int ddn , QString numero, QString email) {

    QSqlQuery q ;
    q.prepare("UPDATE ENTREPRENEURS SET  NOM = :v2, TYPE =:v3 , QNT_STOCK = :v4, DISPONIBILITE = :v5, DESCRIPTION = :v6 WHERE ID = :v1 ") ;
    q.bindValue(":v1",cin) ;
    q.bindValue(":v2",name) ;
    q.bindValue(":v3",prenom) ;
    q.bindValue(":v4",ddn) ;
    q.bindValue(":v5",numero) ;
    q.bindValue(":v6",email) ;
    return q.exec() ;

}

bool entreprneur::Delete_element(int x ) {
      QSqlQuery q ;
      q.prepare("DELETE FROM EQUIPEMENTS WHERE ID = :id ") ;
      q.bindValue(":id",x) ;
      return q.exec() ;
}

