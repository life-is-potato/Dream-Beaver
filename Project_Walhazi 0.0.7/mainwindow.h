#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"equipments.h"
#include"entreprneur.h"
#include"formation.h"
#include"sponsors.h"
#include"project.h"
#include"arduino_equipment.h"
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

#include <QFile>
#include <QTextStream>
#include <QCheckBox>

#include <QThread>
#include <QDateTime>

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
    void clear_chart_widget2();
    void chart_render() ;
    void chart_render2();
    void clear_chart_widget3() ;
    void chart_render3() ;
    void clear_chart_widget4() ;
    void chart_render4() ;
    bool isAlpha(const QString str) ;
    bool isInteger(const int x) ;
    void checkDataChanges() ;


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
    //Entrepreneur
    void setTimes();
    void setArial();
    void size(int n);
    void setred();
    void setwhite();
    void setblack();
    void setyellow();
    void setblue();
    void setgreen();
    void on_edit_clicked();
    void on_file_clicked();
    void on_pdf_2_clicked();
    void on_txt_clicked();
    void on_left_clicked();
    void on_center_clicked();
    void on_right_clicked();
    void on_alignement_clicked();
    void on_entreperneurs_clicked();
    void handleItemDoubleClicked(const QModelIndex &index);
    void on_add_user_clicked();
    void on_adduser_clicked();
    void on_modifyuser_clicked();
    void handleItemClicked(const QModelIndex &index);
    void on_deleteu_clicked();
    void on_pdfuser_clicked();
    void on_sortuser_clicked();
    void on_pointsbutton_clicked();
    void rechercheProjets(const QString &searchText);
    void handleSliceClicked(QPieSlice *slice);
    void on_achivement1_clicked(bool checked);
    void on_achivement2_clicked(bool checked);
    void on_achivement3_clicked(bool checked);
    void on_achivement4_clicked(bool checked);
    void on_achivement5_clicked(bool checked);
    void loadAchivements(QString cin);
    void on_adduserfor_clicked();
    void on_savecheck_clicked();
    //formation
    void on_formation_clicked();
    void on_add_formation_clicked();
    //void on_back_clicked();
    void on_add_form_clicked();
    void on_tableView_3_activated(const QModelIndex &index);
    //void on_back_for_clicked();
    void on_modify_formation_clicked();
    void on_delete_formation_clicked();
    void on_search_button_f_clicked();
    void on_search_formation_textChanged(const QString &arg1);
    void on_tri_formation_clicked();
    void on_tri_typefor_clicked();
    void on_tri_nbrfor_clicked();
    void on_pdf_formation_clicked();
    void applyCurrentFormat();
    //sponsors
    void on_sponsors_clicked();
    void on_adds_clicked();
    //void on_back_clicked();
    void on_add_spon_clicked();
    //void on_back_2_clicked();
    void on_modify_spon_clicked();
    void on_delete_spon_clicked();
    void on_search_button_s_clicked();
    void on_search_bar_s_textChanged(const QString &arg1);
    void on_tri_s_clicked();
    void on_pdf_s_clicked();
    void on_tri_za_clicked();
    void on_tri_az_clicked();
    void on_tableView_5_activated(const QModelIndex &index);
    //projet
    void on_project_clicked();
    void on_add_project_clicked();
    void on_add_projet_clicked();
    void on_delete_project();
    void on_modify_project();
    void on_tableView_6_activated(const QModelIndex &index);
    void on_searchengine_clicked();

    void on_search_btn_clicked();

    void on_arduino_clicked();

    void on_add_s_clicked();

    void on_chatbot_send_clicked();

    void on_historique_clicked();

    void on_add_qnt_clicked();

private:
    QColor currentColor;
    QFont currentFont;
    QTextCharFormat currentFormat;
    Ui::MainWindow *ui;
    Equipments * e ;
    entreprneur * a ;
    Formations *f;
    sponsors s;
    sponsors Stmp;
    project *p;
    int i ;
    QModelIndex selectedIndex;
    QRectF circleRect;
    bool isResizing;
    QPointF lastMousePos;
    arduino_equipment ard ;
    QByteArray data ;

};
#endif // MAINWINDOW_H






