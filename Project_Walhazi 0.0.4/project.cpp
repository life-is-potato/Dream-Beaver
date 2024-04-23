#include "project.h"
#include "mainwindow.h"


QStandardItemModel * project::afficher() {
    int rows ;
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,"ID") ;
    model->setHeaderData(1,Qt::Horizontal,"Name") ;
    model->setHeaderData(2,Qt::Horizontal,"Budget") ;
    model->setHeaderData(3,Qt::Horizontal,"Client") ;

    //l query mta walhezi  :
    QSqlQuery query ;
    query.exec("SELECT * FROM PROJETS ") ;

    while (query.next()) {
        rows = model->rowCount() ;
        model->insertRow(rows) ;
        for(int i = 0 ; i < 4 ; i++ ){
             model->setData(model->index(rows,i),query.value(i).toString());
       }
    }
    return model ;
}

bool project::Add_element(int id, QString name, float budget, int client, QString desc) {
    QSqlQuery q;

    q.prepare("INSERT INTO PROJETS(ID, NOM, BUDGET, CLIENT, DESCRIPTION) VALUES(:v1, :v2, :v4, :v6, :v7)");
    q.bindValue(":v1", id);
    q.bindValue(":v2", name);
    q.bindValue(":v4", budget);
    q.bindValue(":v6", client);
    q.bindValue(":v7", desc);

    if (!q.exec()) {
        qDebug() << "Error executing SQL query:" << q.lastError().text();
        return false;
    }

    return true;
}



bool project::Modify_element(int id , QString name , float budget , int client , QString desc) {

    QSqlQuery q ;
    q.prepare("UPDATE PROJETS SET  NOM = :v2, BUDGET =:v3 , CLIENT = :v4, DESCRIPTION = :v5 WHERE ID = :v1 ") ;
    q.bindValue(":v1",id) ;
    q.bindValue(":v2",name) ;
    q.bindValue(":v3",budget) ;
    q.bindValue(":v4",client) ;
    q.bindValue(":v5",desc) ;
    return q.exec() ;

}

bool project::Delete_element(int x ) {
      QSqlQuery q ;
      q.prepare("DELETE FROM PROJETS WHERE ID = :id ") ;
      q.bindValue(":id",x) ;
      return q.exec() ;
}

