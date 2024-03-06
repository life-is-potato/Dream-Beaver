#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"equipments.h"
#include "sponsors.h"
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


private slots:

    void on_equipments_clicked();

    void on_equipments_clicked(bool checked);

    void on_add_equipment_clicked();

    void on_back_clicked();

    void on_add_equip_clicked();

    void on_back_2_clicked();

    void on_modify_clicked();

    void on_delete_2_clicked();

    void on_search_button_2_clicked();

    void on_search_bar_2_textChanged(const QString &arg1);

    void on_tri_clicked();

    void on_pdf_clicked();


    void on_pushButton_clicked();

    void on_tri_za_clicked();

    void on_tri_az_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Equipments * e ;
    sponsors s;
    sponsors Stmp;
    int i ;
};
#endif // MAINWINDOW_H






