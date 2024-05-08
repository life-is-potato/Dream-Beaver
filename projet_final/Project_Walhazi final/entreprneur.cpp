#include "entreprneur.h"
#include "mainwindow.h"

QStandardItemModel *entreprneur::afficherformation()
{
    int rows = 0;
    QSqlQuery query;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(6);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "TYPE");
    model->setHeaderData(2, Qt::Horizontal, "INSTRUCTEUR");
    model->setHeaderData(3, Qt::Horizontal, "DD");
    model->setHeaderData(4, Qt::Horizontal, "DF");
    model->setHeaderData(5, Qt::Horizontal, "DESCRIPTION");
    QDate currentDate = QDate::currentDate();
    QString formattedDate = currentDate.toString("dd/MM/yy");


    query.prepare("SELECT * FROM FORMATIONS WHERE DD > :currentDate");
    query.bindValue(":currentDate", formattedDate);
    if (query.exec())
    {
        while (query.next())
        {
            rows = model->rowCount();
            model->insertRow(rows);
            for (int i = 0; i < 6; i++)
            {
                model->setData(model->index(rows, i), query.value(i).toString());
            }
        }
    }
    else
    {
        qDebug() << "Query execution failed:" << query.lastError().text();
    }

    return model;
}

QStandardItemModel * entreprneur::afficher() {
    int rows ;
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,"CIN") ;
    model->setHeaderData(1,Qt::Horizontal,"Name") ;
    model->setHeaderData(2,Qt::Horizontal,"Prenom") ;
    model->setHeaderData(3,Qt::Horizontal,"Dob") ;
    model->setHeaderData(4,Qt::Horizontal,"Numero") ;
    model->setHeaderData(5,Qt::Horizontal,"email") ;

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

bool entreprneur::Add_element(int cin, QString email, QDate ddn , int numero , QString nom, QString prenom) {

    QSqlQuery q ;

    q.prepare("INSERT INTO ENTREPRENEURS(CIN,NOM,PRENOM,DDN,NUMERO,EMAIL) VALUES(:v1,:v2,:v3,:v4,:v5,:v6) ") ;
    q.bindValue(":v1",cin) ;
    q.bindValue(":v2",nom) ;
    q.bindValue(":v3",prenom) ;
    q.bindValue(":v4",ddn) ;
    q.bindValue(":v5",numero) ;
    q.bindValue(":v6",email) ;
    return q.exec() ;

}


bool entreprneur::Modify_element(int cin, QString email, QDate ddn , int numero , QString nom, QString prenom) {

    QSqlQuery q ;
    q.prepare("UPDATE ENTREPRENEURS SET  NOM = :v2, PRENOM =:v3 , DDN = :v4, NUMERO = :v5, EMAIL= :v6 WHERE CIN = :v1 ") ;
    q.bindValue(":v1",cin) ;
    q.bindValue(":v2",nom) ;
    q.bindValue(":v3",prenom) ;
    q.bindValue(":v4",ddn) ;
    q.bindValue(":v5",numero) ;
    q.bindValue(":v6",email) ;
    return q.exec() ;

}

bool entreprneur::Delete_element(int n)
{
    QSqlQuery q;
    q.prepare("DELETE FROM ENTREPRENEURS WHERE CIN = :CIN");
    q.bindValue(":CIN", n);
    if (!q.exec()) {
        qDebug() << "Failed to delete row" << q.lastError().text();
        return false;
    } else {
        qDebug() << "row successfully deleted";
        return true;
    }
}
QStandardItemModel* entreprneur::recherche_projet(QString str) {
    int rows;
    QSqlQuery query;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(6);
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "FirstName");
    model->setHeaderData(2, Qt::Horizontal, "LastName");
    model->setHeaderData(3, Qt::Horizontal, "DoB");
    model->setHeaderData(4, Qt::Horizontal, "Number");
    model->setHeaderData(5, Qt::Horizontal, "Email");
    query.prepare("SELECT E.* FROM ENTREPRENEURS E "
                  "INNER JOIN PROJETS P ON E.CIN = P.CLIENT "
                  "WHERE P.NOM = :x");
    query.bindValue(":x", str);

    if (query.exec()) {
        while (query.next()) {
            rows = model->rowCount();
            model->insertRow(rows);
            for (int i = 0; i < 6; i++) {
                model->setData(model->index(rows, i), query.value(i).toString());
            }
        }
    } else {
        qDebug() << "Query failed:" << query.lastError();
    }
    return model;
}
QString entreprneur::getPoints(QString cin)
{
    QSqlQuery query;
    query.prepare("SELECT POINTS FROM ENTREPRENEURS WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    } else {
        return "";
    }
}
QString entreprneur::addPoints(QString cin,int p)
{
    QSqlQuery query;
    p=p+(getPoints(cin)).toInt();
    query.prepare("UPDATE ENTREPRENEURS SET POINTS = :v1 WHERE CIN = :cin");
      query.bindValue(":cin", cin);
      query.bindValue(":v1", p);
      if (query.exec()) {
          return "points updated sucessfuly";
      } else {
          return "failed to update points: "+query.lastError().text();
      }
  }
QString entreprneur::losePoints(QString cin,int p)
{
    QSqlQuery query;
    p=(getPoints(cin)).toInt()-p;
    query.prepare("UPDATE ENTREPRENEURS SET POINTS = :v1 WHERE CIN = :cin");
      query.bindValue(":cin", cin);
      query.bindValue(":v1", p);
      if (query.exec()) {
          return "points updated sucessfuly";
      } else {
          return "failed to update points: "+query.lastError().text();
      }
  }
bool entreprneur::isFormationValid(int formationId)
{
    QSqlQuery query;
    query.prepare("SELECT DD FROM formations WHERE id = :id");
    query.bindValue(":id", formationId);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false; // Return false if query execution fails
    }

    if (query.next()) {
        QDate startDate = query.value(0).toDate();
        QDate currentDate = QDate::currentDate();

        qDebug() << "Formation ID:" << formationId;
        qDebug() << "Start date:" << startDate;
        qDebug() << "Current date:" << currentDate;

        if (currentDate < startDate) {
            return true;
        } else {
        return false;
        }
    } else {
        qDebug() << "Formation not found with ID:" << formationId;
        return false;
    }
}
bool entreprneur::addFreeFormation(QString cin,QString idf){
    if (isFormationValid(idf.toUInt())){
    QSqlQuery query;
    query.prepare("INSERT INTO ENTREPRENEURS_FORMATIONS(ID_ENTR,ID_FORM) VALUES(:v1,:v2)");
    query.bindValue(":v1",cin);
    query.bindValue(":v2",idf);
    return query.exec() ;
    } else {
qDebug() <<"formation bid"<<idf<<"is not valid";
return false;
    }}


