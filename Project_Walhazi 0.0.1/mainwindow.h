#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"equipments.h"
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
    void bar_code(QString) ;


private slots:

    void on_equipments_clicked();

    void on_equipments_clicked(bool checked);

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

private:
    Ui::MainWindow *ui;
    Equipments * e ;
    int i ;
};
#endif // MAINWINDOW_H






