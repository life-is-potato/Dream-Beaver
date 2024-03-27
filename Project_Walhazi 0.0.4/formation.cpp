#include "formation.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

Formations::Formations() {}

QStandardItemModel *Formations::afficher()
{
    int rows;
    QSqlQuery query;
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(7);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "TYPE");
    model->setHeaderData(2, Qt::Horizontal, "INSTRUCTEUR");
    model->setHeaderData(3, Qt::Horizontal, "DD");
    model->setHeaderData(4, Qt::Horizontal, "DF");
    model->setHeaderData(5, Qt::Horizontal, "DESCRIPTION");
    model->setHeaderData(6, Qt::Horizontal, "NB_PARTICIPANTS");

    query.exec("SELECT * FROM FORMATIONS");

    while (query.next())
    {
        rows = model->rowCount();
        model->insertRow(rows);
        for (int i = 0; i < 7; i++)
        {
            model->setData(model->index(rows, i), query.value(i).toString());
        }
    }
    return model;
}

QStandardItemModel *Formations::search_element(const QString &str)
{
    int rows;
    QSqlQuery query;
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(7);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "TYPE");
    model->setHeaderData(2, Qt::Horizontal, "INSTRUCTEUR");
    model->setHeaderData(3, Qt::Horizontal, "DD");
    model->setHeaderData(4, Qt::Horizontal, "DF");
    model->setHeaderData(5, Qt::Horizontal, "DESCRIPTION");
    model->setHeaderData(6, Qt::Horizontal, "NB_PARTICIPANTS");

    query.prepare("SELECT * FROM FORMATIONS WHERE ID LIKE :x || '%' OR TYPE LIKE :x || '%' ");
    query.bindValue(":x", str);

    if (query.exec())
    {
        while (query.next())
        {
            rows = model->rowCount();
            model->insertRow(rows);
            for (int i = 0; i < 7; i++)
            {
                model->setData(model->index(rows, i), query.value(i).toString());
            }
        }
    }
    else
    {
        qDebug() << "Query failed:" << query.lastError();
    }

    return model;
}

bool Formations::Add_element(int id, QString type, QString instructeur, QDate dateDebut, QDate dateFin, QString description, int nbParticipants)
{
    QSqlQuery q;
    q.prepare("INSERT INTO FORMATIONS VALUES(:v1,:v2,:v3,:v4,:v5,:v6,:v7,:NULL) ");
    q.bindValue(":v1", id);
    q.bindValue(":v2", type);
    q.bindValue(":v3", instructeur);
    q.bindValue(":v4", dateDebut);
    q.bindValue(":v5", dateFin);
    q.bindValue(":v7", description);
    q.bindValue(":v6", nbParticipants);
    return q.exec();
}

bool Formations::Modify_element(int id, QString type, QString instructeur, QDate dateDebut, QDate dateFin, QString description, int nbParticipants)
{
    QSqlQuery q;
    q.prepare("UPDATE FORMATIONS SET TYPE = :v2, INSTRUCTEUR = :v3, DATEDEBUT = :v4, DATEFIN = :v5, DESCRIPTION = :v6, NB_PARTICIPANTS = :v7 WHERE ID = :v1 ");
    q.bindValue(":v1", id);
    q.bindValue(":v2", type);
    q.bindValue(":v3", instructeur);
    q.bindValue(":v4", dateDebut);
    q.bindValue(":v5", dateFin);
    q.bindValue(":v6", description);
    q.bindValue(":v7", nbParticipants);

    return q.exec();
}

bool Formations::Delete_element(int x)
{
    QSqlQuery q;
    q.prepare("DELETE FROM FORMATIONS WHERE ID = :id ");
    q.bindValue(":id", x);

    return q.exec();
}


