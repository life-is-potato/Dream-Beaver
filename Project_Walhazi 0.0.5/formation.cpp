#include "formation.h"
#include "mainwindow.h"


QStandardItemModel * formation::afficher() {
    int rows ;
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(7);
    model->setHeaderData(0,Qt::Horizontal,"ID") ;
    model->setHeaderData(1,Qt::Horizontal,"Type") ;
    model->setHeaderData(2,Qt::Horizontal,"Instructeur") ;
    model->setHeaderData(3,Qt::Horizontal,"DD") ;
    model->setHeaderData(4,Qt::Horizontal,"DF") ;
    model->setHeaderData(5,Qt::Horizontal,"Nb_participants") ;
    model->setHeaderData(6,Qt::Horizontal,"Description") ;

    //l query mta walhezi  :
    QSqlQuery query ;
    query.exec("SELECT * FROM FORMATIONS ") ;

    while (query.next()) {
        rows = model->rowCount() ;
        model->insertRow(rows) ;
        for(int i = 0 ; i < 7 ; i++ ){
             model->setData(model->index(rows,i),query.value(i).toString());
       }
    }
    return model ;
}

bool formation::Add_element(int id, int type, QString instruction , QString dd, QString df, int nb_part, QString desc) {
    QSqlQuery q;

    q.prepare("INSERT INTO FORMATIONS(ID, TYPE, INSTRUCTEUR, DD, DF, NB_PARTICIPANTS, DESCRIPTION) "
              "VALUES(:v1, :v2, :v3, TO_DATE(:v4, 'DD/MM/YYYY'), TO_DATE(:v5, 'DD/MM/YYYY'), :v6, :v7)");
    q.bindValue(":v1", id);
    q.bindValue(":v2", type);
    q.bindValue(":v3", instruction);
    q.bindValue(":v4", dd);
    q.bindValue(":v5", df);
    q.bindValue(":v6", nb_part);
    q.bindValue(":v7", desc);

    return q.exec();
}


bool formation::Modify_element(int id, int type, QString instruction, QString dd, QString df, int nb_part, QString desc) {
    QSqlQuery q;
    q.prepare("UPDATE FORMATIONS SET TYPE = :v2, INSTRUCTEUR = :v3, DD = TO_DATE(:v4, 'DD/MM/YYYY'), DF = TO_DATE(:v5, 'DD/MM/YYYY'), NB_PARTICIPANTS = :v6, DESCRIPTION = :v7 WHERE ID = :v1");
    q.bindValue(":v1", id);
    q.bindValue(":v2", type);
    q.bindValue(":v3", instruction);
    q.bindValue(":v4", dd);
    q.bindValue(":v5", df);
    q.bindValue(":v6", nb_part);
    q.bindValue(":v7", desc);
    return q.exec();
}


bool formation::Delete_element(int x ) {
      QSqlQuery q ;
      q.prepare("DELETE FROM FORMATIONS WHERE ID = :id ") ;
      q.bindValue(":id",x) ;
      return q.exec() ;
}


formation::formation()
{

}
