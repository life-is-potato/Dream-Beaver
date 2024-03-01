#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "costumer.h"
#include <QMainWindow>
#include "connection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private :
    Ui::MainWindow *ui;
    Costumer* c;
    QModelIndex selectedIndex;


private slots :
    void handleItemDoubleClicked(const QModelIndex &index);
    void on_add_user_clicked();
    void on_Users_clicked();
    void on_adduser_clicked();
    void on_modifyu_clicked();
    void handleItemClicked(const QModelIndex &index);
    void on_modify_user_clicked();
};
#endif // MAINWINDOW_H
