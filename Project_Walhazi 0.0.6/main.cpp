#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include<qmessagebox.h>
#include"databaseconnection.h"
int main(int argc, char *argv[])
{
     DataBaseConnection fab_lab ;
    QApplication a(argc, argv);
    login loginDialog;
    loginDialog.setWindowFlags(Qt::FramelessWindowHint);
    loginDialog.setAttribute(Qt::WA_TranslucentBackground);
     if(fab_lab.connect()){
         if (loginDialog.exec() == QDialog::Accepted) {
             MainWindow w;
             w.show();
             return a.exec();
         } else {
             return -1;
         }
     }
     else {
        QMessageBox::critical(nullptr,"winek","winek") ;
        return -1;
     }
}

