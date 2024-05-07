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
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QSqlQuery query;

        query.prepare("INSERT INTO SPONSORES (ID, NOM, EMAIL, NUMERO, TYPE) "
                      "VALUES (:ID, :NOM, :EMAIL, :NUMERO, :TYPE)");

        query.bindValue(":ID", id);
        query.bindValue(":NOM", nom);
        query.bindValue(":EMAIL", email);
        query.bindValue(":NUMERO", num);
        query.bindValue(":TYPE", type);

        QString dataString = QString("AJOUT de : \nID: %1\nNOM: %2\nEMAIL: %3\nNUMERO: %4\nTYPE: %5\nDatetime: %6")
            .arg(id)
            .arg(nom)
            .arg(email)
            .arg(num)
            .arg(type)
            .arg(currentDateTime.toString(Qt::ISODate));


            QString filePath = "historique.txt";
            if (query.exec()) {
                QFile file(filePath);
                if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
                    QTextStream out(&file);
                    out << dataString << "\n";
                    out << "-----------------------------" ;
                    file.close();
                } else {
                    qDebug() << "8alet" ;
                }
            return true;
        }
    return false ;

}
QStandardItemModel * sponsors:: afficher()
{
    int rows;
    QSqlQuery query;
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "NOM");
    model->setHeaderData(2, Qt::Horizontal, "EMAIL");
    model->setHeaderData(3, Qt::Horizontal, "NUMERO");
    model->setHeaderData(4, Qt::Horizontal, "TYPE");
    query.exec("SELECT * FROM SPONSORES");

    while (query.next())
    {
        rows = model->rowCount();
        model->insertRow(rows);
        for (int i = 0; i < 5; i++)
        {
            model->setData(model->index(rows, i), query.value(i).toString());
        }
    }
    return model;
}

bool sponsors::modifier(int id)
{
                QSqlQuery query;
                QDateTime currentDateTime = QDateTime::currentDateTime();

                query.prepare("UPDATE SPONSORES SET ID=:ID, NOM = :NOM, EMAIL=:EMAIL, NUMERO=:NUMERO, TYPE=:TYPE WHERE ID=:ID");
                query.bindValue(":ID", id);
                query.bindValue(":NOM", nom);
                query.bindValue(":EMAIL", email);
                query.bindValue(":NUMERO", num);
                query.bindValue(":TYPE", type);


                QString dataString = QString("\nMODIFICATION de : \nID: %1\nNOM: %2\nEMAIL: %3\nNUMERO: %4\nTYPE: %5\nDatetime: %6")
                    .arg(id)
                    .arg(nom)
                    .arg(email)
                    .arg(num)
                    .arg(type)
                    .arg(currentDateTime.toString(Qt::ISODate));


                    QString filePath = "historique.txt";
                    if (query.exec()) {
                        QFile file(filePath);
                        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
                            QTextStream out(&file);
                            out << dataString << "\n";
                            out << "-----------------------------" ;
                            file.close();
                        } else {
                            qDebug() << "8alet" ;
                        }
                    return true;
                }
            return false ;
}
bool sponsors::supprimer(int id)
{
    QSqlQuery query;
    QDateTime currentDateTime = QDateTime::currentDateTime();

        query.prepare("DELETE FROM SPONSORES WHERE ID = :ID");
        query.bindValue(":ID",id);


        QString dataString = QString("\nSUPPRESSION de : \nID: %1\nDatetime: %6")
            .arg(id)
            .arg(currentDateTime.toString(Qt::ISODate));


            QString filePath = "historique.txt";
            if (query.exec()) {
                QFile file(filePath);
                if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
                    QTextStream out(&file);
                    out << dataString << "\n";
                    out << "-----------------------------" ;
                    file.close();
                } else {
                    qDebug() << "8alet" ;
                }
            return true;
        }
    return false ;
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
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));

    query.prepare("SELECT * FROM SPONSORES WHERE NOM LIKE :x || '%' ");
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





              model->setQuery("SELECT* FROM SPONSORES ORDER BY LOWER(NOM) ASC");

              model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO"));
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
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));



    return model;

}

QString sponsors::chatbot(QString usermessgae){

    QString botResponse;
    QString userMessage = usermessgae ;
    QSqlQuery query;
    int rowcount = 0 ;


    if (usermessgae == "combien de sponsor y'a t'il") {
        query.prepare("SELECT * FROM SPONSORES");

        if (query.exec()) {
            while(query.next()){
                rowcount++ ;
            }
            QString response = QString::number(rowcount);
            botResponse = "- il y a " + response + " de sponsores " ;
        }
    }

    if (usermessgae == "chercher ce sponsor par son type physique"){

        query.prepare("SELECT * FROM SPONSORES WHERE TYPE LIKE 'physique' ") ;
       if (query.exec()){
           while (query.next()) {
                      QString id = query.value(0).toString();
                      QString nom = query.value(1).toString();
                      QString email = query.value(2).toString();
                      QString numero = query.value(3).toString();
                      QString type = query.value(4).toString();

                      botResponse += "- ID: " + id + "\n";
                      botResponse += "- Nom: " + nom + "\n";
                      botResponse += "- Email: " + email + "\n";
                      botResponse += "- Numero: " + numero + "\n";
                      botResponse += "- Type: " + type + "\n";

                  }
              } else {
                  qDebug() << "Query execution failed: " << query.lastError();
              }
       }

    if (usermessgae == "chercher ce sponsor par son type morale"){

        query.prepare("SELECT * FROM SPONSORES WHERE TYPE LIKE 'morale' ") ;
       if (query.exec()){
           while (query.next()) {
                      QString id = query.value(0).toString();
                      QString nom = query.value(1).toString();
                      QString email = query.value(2).toString();
                      QString numero = query.value(3).toString();
                      QString type = query.value(4).toString();

                      botResponse += "- ID: " + id + "\n";
                      botResponse += "- Nom: " + nom + "\n";
                      botResponse += "- Email: " + email + "\n";
                      botResponse += "- Numero: " + numero + "\n";
                      botResponse += "- Type: " + type + "\n";

                  }
              } else {
                  qDebug() << "Query execution failed: " << query.lastError();
              }
       }

    return botResponse ;
}

QString sponsors::historique(){
    QString result ;
    QFile file("historique.txt");
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                result = in.readAll();
                file.close();
            } else {
                qDebug() << "Impossible d'ouvrir le fichier";
            }
      return result ;
}
