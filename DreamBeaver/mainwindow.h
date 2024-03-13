#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "costumer.h"
#include <QMainWindow>
#include "connection.h"
#include <QFileDialog>
#include <QMessageBox>
#include "sponsors.h"
#include "equipments.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts>

#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QMap>

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
    int i;
    Equipments * e ;
    Ui::MainWindow *ui;
    Costumer* c;
    QModelIndex selectedIndex;
    sponsors s;
    sponsors Stmp;


private slots :
    void handleItemDoubleClicked(const QModelIndex &index);
    void on_add_user_clicked();
    void on_Users_clicked();
    void on_adduser_clicked();
    void on_modifyu_clicked();
    void handleItemClicked(const QModelIndex &index);
    void on_modify_user_clicked();
    void rechercheProjets(const QString &searchtext);
    void on_pdf_clicked();
    void on_sort_clicked();
    //equipments
    void on_equipments_clicked();
    void on_add_equipment_2_clicked();
    void on_add_equip_clicked();
    void on_tableView_3_activated(const QModelIndex &index);
    void on_modify_clicked();
    void on_delete_2_clicked();
    void on_search_button_3_clicked();
    void on_search_bar_3_textChanged(const QString &arg1);
    void on_tri_2_clicked();
    void on_tri_type_2_clicked();
    void on_tri_qnt_2_clicked();
    void on_pdf_3_clicked();
    //sponsors
    void on_sponsors_clicked();
    void on_add_spon_clicked();
    void on_add_spons_clicked();
    void on_modify_spon_clicked();
    void on_delete_spon_clicked();
    void on_search_button_s_clicked();
    void on_search_bars_textChanged(const QString &arg1);
    void on_tris_clicked();
    void on_pdfs_clicked();
    void on_tri_za_clicked();
    void on_tri_az_clicked();
    void on_tableView_4_activated(const QModelIndex &index);
};
#endif // MAINWINDOW_H
