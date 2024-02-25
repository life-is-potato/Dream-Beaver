#include "mainwindow.h"
#include "databaseconnection.h"
#include <QApplication>
#include<QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DataBaseConnection fab_lab ;

    if(fab_lab.connect()){
         w.show() ;
    }
    else {
       QMessageBox::critical(nullptr,"winek","winek") ;
    }
    return a.exec();
}
