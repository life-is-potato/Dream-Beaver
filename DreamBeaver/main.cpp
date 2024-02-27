#include "mainwindow.h"

#include <QApplication>
#include<qmessagebox.h>
#include"connection.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection d ;

if (d.createconnect()){
    w.show();
}
else {
    QMessageBox::information(NULL, "Hello World!", "Hi!");
}

    return a.exec();
}
