#include "sponsors.h"
#include<QSqlQuery>
#include"mainwindow.h"


sponsors::~sponsors()
{
    delete ui;
}

sponsors::sponsors()
{
    this->id=0;
    this->nom="";
    this->email="";
    this->num=0;
    this->type="";
}
sponsors::sponsors(int id,QString nom, QString email,int num, QString type)
{
    this->id=id;
    this->nom=nom;
    this->email=email;
    this->num=num;
    this->type=type;
}
void sponsors::setid(int id){this->id=id;}
void sponsors::setnom(QString nom){this->nom=nom;}
void sponsors::setemail(QString email){this->email=email;}
void sponsors::setnum(int num){this->num=num;}
void sponsors::settype(QString type){this->type=type;}

int sponsors::get_id(){return this->id;}
QString sponsors::get_nom(){return this->nom;}
QString sponsors::get_email(){return this->email;}
int sponsors::get_num(){return this->num;}
QString sponsors::get_type(){return this->type;}

bool sponsors::ajouter()
{

    QSqlQuery query;  //Un objet QSqlQuery nommé query est créé. Cet objet est utilisé pour exécuter des requêtes SQL sur la base de données.
        //Conversion des données en chaînes de caractères

        QString res = QString::number(id);
        QString res1 = QString::number(num);
        query.prepare("INSERT INTO SPONSORS (ID, NOM, EMAIL, NUM, TYPE) "

                      "VALUES (:ID, :NOM, :EMAIL, :NUM, :TYPE)");

        query.bindValue(":ID", res);
        query.bindValue(":NOM", nom);
        query.bindValue(":EMAIL", email);
        query.bindValue(":NUM", res1);
        query.bindValue(":TYPE", type);

        return query.exec();
}

QSqlQueryModel * sponsors::afficher()
{
        QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM SPONSORS");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));


        return model ;

}
bool sponsors::modifier(int id)
{
    QSqlQuery query;

                QString res = QString::number(id);
                QString res1 = QString::number(num);

                query.prepare("UPDATE SPONSORS SET ID=:ID, NOM = :NOM, EMAIL=:EMAIL, NUM=:NUM, TYPE=:TYPE WHERE ID=:ID");
                query.bindValue(":ID", res);
                query.bindValue(":NOM", nom);
                query.bindValue(":EMAIL", email);
                query.bindValue(":NUM", res1);
                query.bindValue(":TYPE", type);
                return query.exec();
}
bool sponsors::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);

        query.prepare("DELETE FROM SPONSORS WHERE ID = :ID");
        query.bindValue(":ID",res);

        return query.exec();
}

QStandardItemModel * sponsors::search_element(QString str)
{
    int rows;
    QSqlQuery query;
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));

    query.prepare("SELECT * FROM SPONSORS WHERE NOM LIKE :x || '%' ");
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
QSqlQueryModel * sponsors::afficheA_Z()

{

    QSqlQueryModel* model=new QSqlQueryModel();





              model->setQuery("SELECT* FROM SPONSORS ORDER BY LOWER(NOM) ASC");

              model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));



    return model;

}



QSqlQueryModel * sponsors::afficheZ_A()

{

    QSqlQueryModel* model=new QSqlQueryModel();





              model->setQuery("SELECT* FROM SPONSORS ORDER BY LOWER(NOM) DESC");

              model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));



    return model;

}

