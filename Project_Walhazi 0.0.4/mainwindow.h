#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"equipments.h"
#include"entreprneur.h"
#include"formation.h"
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

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct FormationInfo {
    int id;
    QString instructeur;
    QDate dateDebut;
    QDate dateFin;
};
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

    void on_project_clicked();

    void on_adds_clicked();

    //Entrepreneur
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
    void populateCalendarWithFormations();
    void on_calendarWidget_clicked(const QDate &date);
    void checkAbsence();
    void sendEmailToEntrepreneur(const int &entrepreneurID);
    void emailStatus(const QString &status);
    void on_mailing_clicked();

    void on_star_clicked();
    void replyFinished(QNetworkReply *reply);
private:
    Ui::MainWindow *ui;
    Equipments * e ;
    entreprneur * a ;
    Formations *f;
    int i ;
    QModelIndex selectedIndex;
    QVector<FormationInfo> formationInfoList;
    QNetworkAccessManager *manager;

};
#endif // MAINWINDOW_H






