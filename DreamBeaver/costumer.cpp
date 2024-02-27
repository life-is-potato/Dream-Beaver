#include "costumer.h"
    int Costumer::getCin(){
        return cin;
    }
    QDate Costumer::getDoB(){
        return dOb;
    }
    int Costumer::getNumber(){
        return number;
    }
    QString Costumer::getFname(){
        return fName;
    }
    QString Costumer::getLname()
    {
        return lName;
    }
    QString  Costumer::getEmail()
    {
        return email;
    }
    void Costumer::setCin(int nvCin)
    {
        cin=nvCin;
    }
    void Costumer::setDoB(QDate nvDoB) {
        dOb=nvDoB;
    }
    void Costumer::setFname(QString nvFname)
    {
        fName=nvFname;
    }
    void Costumer::setLname(QString nvLname){
        lName=nvLname;
    }
    void Costumer::setEmail(QString nvEmail){
        email=nvEmail;
    }

    bool Costumer::AjouterClient(int cinnv, QDate nvdob, int nvnumber, QString nvfName, QString nvlName, QString nvemail)
    {

        QSqlQuery q ;

        q.prepare("INSERT INTO ENTREPRENEURS(CIN,NOM,PRENOM,DDN,NUMERO,EMAIL) VALUES(:v1,:v2,:v3,:v4,:v5,:v6) ") ;
        q.bindValue(":v1",cinnv) ;
        q.bindValue(":v2",nvfName) ;
        q.bindValue(":v3",nvlName) ;
        q.bindValue(":v4",nvdob) ;
        q.bindValue(":v5",nvnumber) ;
        q.bindValue(":v6",nvemail) ;
        if (! q.exec()) {
            qDebug() << "8alet" ;
            return false;
        }
        else {
            return true ;
        }
    }
    QStandardItemModel* Costumer::afficher() {
        int rows ;
        QStandardItemModel * model = new QStandardItemModel();
        model->setColumnCount(5);
        model->setHeaderData(0,Qt::Horizontal,"CIN");
        model->setHeaderData(1,Qt::Horizontal,"FirstName");
        model->setHeaderData(2,Qt::Horizontal,"LastName");
        model->setHeaderData(3,Qt::Horizontal,"DoB");
        model->setHeaderData(4,Qt::Horizontal,"Adress");
        model->setHeaderData(4,Qt::Horizontal,"Email");
        model->setHeaderData(4,Qt::Horizontal,"Number");
        QSqlQuery query ;
        query.exec("SELECT* FROM ENTREPRENEURS") ;
        // (query.next()) ==> next query
        while (query.next()) {
            rows = model->rowCount() ;
            model->insertRow(rows) ;
            for(int i = 0 ; i < 5 ; i++ ){
                 model->setData(model->index(rows,i),query.value(i).toString());
           }
        }
        return model ;
    }
    bool Costumer::EffacerClient(int n)
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
