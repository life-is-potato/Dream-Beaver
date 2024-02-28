#ifndef SPONSORS_H
#define SPONSORS_H

#include <QDialog>
#include<QString>
#include <QSqlQueryModel>
#include<QStandardItemModel>

namespace Ui {
class sponsors;
}

class sponsors : public QDialog
{
    Q_OBJECT

public:
    ~sponsors();
    sponsors();
    sponsors(int, QString, QString, int, QString);

    //setters
    void setid (int );
    void setnum (int );
    void setnom (QString );
    void setemail (QString );
    void settype (QString );

    //getters
    int get_id();
    int get_num();
    QString get_nom();
    QString get_email();
    QString get_type();

    //fonction
    bool ajouter();
    bool modifier(int);
    bool supprimer(int);
    QSqlQueryModel * affichage ();
    QStandardItemModel * afficher();


private:
    Ui::sponsors *ui;
    int id,num ;
    QString nom, email,type;
};

#endif // SPONSORS_H
