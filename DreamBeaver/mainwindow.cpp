#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tableView, &QAbstractItemView::doubleClicked, this, &MainWindow::handleItemDoubleClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::handleItemDoubleClicked(const QModelIndex &index)
{
    int row = index.row();
    int col=0;
    //takhou cin doubel clickitha
    QVariant currentcin=ui->tableView->model()->data(ui->tableView->model()->index(row,col));
        int cin=currentcin.toInt();
        bool test= c->EffacerClient(cin);
        if (test)
        {
            ui->tableView->model()->removeRow(row);
        } else
        {
            qDebug()<<"Failed deleting the row";
        }
}


void MainWindow::on_add_user_clicked()
{
    int cin = ui->cin->text().toInt();
    QString fname = ui->fname->text();
    QString lname= ui->lname->text() ;
    QDate birthday = ui->birthday->date() ;
    QString adress=ui->adress->text();
    QString email=ui->email->text();
    int number = ui->phone_2->text().toInt();
    if (c->AjouterClient(cin,birthday,number,fname,lname,email)) {
           ui->cin->clear();
           ui->fname->clear();
           ui->lname->clear();
           ui->email->clear();
           ui->phone_2->clear();
           ui->adress->clearMask();
           ui->birthday->clearMask();
           ui->stackedWidget->setCurrentIndex(0);
    }
    else {
          // QMessageBox::critical(nullptr,"zid thabet","bhim") ;
    }
}
void MainWindow::on_Users_clicked()
{
   ui->stackedWidget->setCurrentIndex(1) ;
   ui->tableView->setModel(c->afficher());
}
void MainWindow::on_adduser_clicked()
{
    ui->stackedWidget->setCurrentIndex(0) ;
}

