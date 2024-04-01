#include "pub.h"
#include "mainwindow.h"


QStandardItemModel * pub::afficher() {
    int rows ;
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(7);
    model->setHeaderData(0,Qt::Horizontal,"ID") ;
    model->setHeaderData(1,Qt::Horizontal,"Name") ;
    model->setHeaderData(2,Qt::Horizontal,"Type") ;
    model->setHeaderData(3,Qt::Horizontal,"Cout") ;
    model->setHeaderData(4,Qt::Horizontal,"DD") ;
    model->setHeaderData(5,Qt::Horizontal,"DF") ;
    model->setHeaderData(6,Qt::Horizontal,"PROJET_ID") ;

    //l query mta walhezi  :
    QSqlQuery query ;
    query.exec("SELECT * FROM PUBS ") ;

    while (query.next()) {
        rows = model->rowCount() ;
        model->insertRow(rows) ;
        for(int i = 0 ; i < 7 ; i++ ){
             model->setData(model->index(rows,i),query.value(i).toString());
       }
    }
    return model ;
}

bool pub::Add_element(int id , QString name , int type , int cout , QString dd, QString df , int id_projet ) {

    QSqlQuery q ;

    q.prepare("INSERT INTO PUBS(ID,NOM,TYPE,COUT,DD,DF,PROJET_ID) VALUES(:v1,:v2,:v3,:v4,TO_DATE(:v5,'DD/MM/YYYY'),TO_DATE(:v6,'DD/MM/YYYY'),:v7) ") ;
    q.bindValue(":v1",id) ;
    q.bindValue(":v2",name) ;
    q.bindValue(":v3",type) ;
    q.bindValue(":v4",cout) ;
    q.bindValue(":v5",dd) ;
    q.bindValue(":v6",df) ;
    q.bindValue(":v7",id_projet) ;
    return q.exec() ;
}


bool pub::Modify_element(int id , QString name , int type , int cout , QString dd, QString df , int id_projet) {

    QSqlQuery q ;
    q.prepare("UPDATE PUBS SET  NOM = :v2, TYPE =:v3 , QNT_STOCK = :v4, DISPONIBILITE = :v5, DESCRIPTION = :v6 WHERE ID = :v1 ") ;
    q.bindValue(":v1",id) ;
    q.bindValue(":v2",name) ;
    q.bindValue(":v3",type) ;
    q.bindValue(":v4",cout) ;
    q.bindValue(":v5",dd) ;
    q.bindValue(":v6",df) ;
    q.bindValue(":v7",id_projet) ;
    return q.exec();

}

bool pub::Delete_element(int x ) {
      QSqlQuery q ;
      q.prepare("DELETE FROM PUBS WHERE ID = :id ") ;
      q.bindValue(":id",x) ;
      return q.exec() ;
}



pub::pub()
{

}
