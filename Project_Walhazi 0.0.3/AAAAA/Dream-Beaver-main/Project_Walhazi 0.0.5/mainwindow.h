#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"equipments.h"
#include"entreprneur.h"
#include"pub.h"
#include"formation.h"
#include"project.h"
#include"search_engine.h"
#include"sponsors.h"
#include <QtSql>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QTextDocument>
#include <QPdfWriter>

#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>


#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void clear_chart_widget() ;
    void chart_render() ;
    bool isAlpha(const QString str) ;
    bool isInteger(const int x) ;


private slots:

    void on_equipments_clicked();

    void on_add_equipment_clicked();

    void on_back_clicked();

    void on_add_equip_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_back_2_clicked();

    void on_modify_clicked();

    void on_delete_2_clicked();

    void on_search_button_2_clicked();

    void on_search_bar_2_textChanged(const QString &arg1);

    void on_tri_clicked();

    void on_tri_type_clicked();

    void on_tri_qnt_clicked();

    void on_pdf_clicked();

    void on_pushButton_clicked();

    void on_entreperneurs_clicked();

    void on_project_clicked();

    void on_formation_clicked();

    void on_adds_clicked();

    void on_add_project_clicked();

    void on_add_projet_clicked();

    void on_tableView_3_activated(const QModelIndex &index);

    void on_modify_project_clicked();

    void on_delete__project_clicked();

    void on_add_equipment_2_clicked();

    void on_add_entr_clicked();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_modify_project_2_clicked();

    void on_delete__project_2_clicked();

    void on_add_equipment_4_clicked();

    void on_add_entr_2_clicked();

    void on_tableView_4_activated(const QModelIndex &index);

    void on_modify_project_3_clicked();

    void on_delete__project_3_clicked();

    void on_add_equipment_5_clicked();

    void on_add_entr_3_clicked();

    void on_tableView_5_activated(const QModelIndex &index);

    void on_modify_pub_clicked();

    void on_delete__pub_clicked();

    void on_pushButton_2_clicked();

    void on_search_button_clicked();

    void on_sponsors_clicked();

    void on_add_equipment_6_clicked();

    void on_add_sponsor_clicked();

    void on_tableView_7_activated(const QModelIndex &index);

    void on_modify_sponsor_clicked();

    void on_delete_sponsor_clicked();

private:
    Ui::MainWindow *ui;
    Equipments * e ;
    entreprneur * a ;
    project *p ;
    search_engine *sea ;
    sponsors *s ;
    pub *pu ;
    formation * f ;
    int i ;
};
#endif // MAINWINDOW_H






