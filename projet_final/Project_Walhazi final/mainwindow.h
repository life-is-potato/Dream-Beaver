#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"equipments.h"
#include"entreprneur.h"
#include"formation.h"
#include"sponsors.h"
#include"project.h"
#include"arduino_equipment.h"
#include"email.h"
#include"formationwidget.h"
#include <QtSql>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QTextDocument>
#include <QPdfWriter>

#include <QPixmap>
#include <QImage>
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

#include <QtNetwork>
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
    int projectID;
    bool MaquetteShowing;

public slots:

    void clear_chart_widget(QLayout *) ;

    void chart_render() ;
    void chart_render2();
    void chart_render3() ;
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
    void populateCalendarWithFormations();
    void on_calendarWidget_clicked(const QDate &date);
    void checkAbsence();
    void emailStatus(const QString &status);
    void on_mailing_clicked();
    void on_star_clicked();
    void replyFinished(QNetworkReply *reply);
    void checkAbsences();
    void on_yes_clicked();
    void on_no_clicked();
    void checkRFIDCard();
    void RFID(int b);
    void on_pushButton_3_clicked();
    void on_pushButton_7_clicked();
    void addFormationWidget(const FormationData &data, QGridLayout *layout, int row, int column);
    void handleFormationClicked();
    void on_search_button_f_2_clicked();
    void on_search_formation_2_textChanged();
    void clearFormationWidgets();
    void populateFormationWidgets(const QVector<FormationData> &searchResults);
    void sortFormationWidgetsByDate();
    void refreshFormationWidgets();
    void on_tri_typefor_2_clicked();
    void sortFormationWidgetsByParticipants();
    void on_tri_nbrfor_2_clicked();
    void on_tri_formation_2_clicked();
    void on_pdf_formation_2_clicked();
    void on_add_formation_2_clicked();
    void on_mailing_2_clicked();
    void on_star_2_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_10_clicked();
    void tableView_6_handleDoubleClick(const QModelIndex &index);
    void on_delete__project_clicked();
    void on_modify_project_clicked();
    void on_search_button_4_clicked();
    void on_search_bar_4_textChanged(const QString &arg1);
    void on_pdf_3_clicked();
    void budgetChartRender();
    void tableView_6_handleClick(const QModelIndex &index);
    void on_pushButton_9_clicked();
    void searchSimilarImages();


    QVector<FormationData> retrieveFormationDataFromDatabase(const QString &str);
    FormationData extractFormationData(QStandardItemModel *model, int index);
    QString getEmailById(int entrepreneurID);

    void on_back_3_clicked();

    void on_back_7_clicked();

    void on_back_5_clicked();

    void on_back_4_clicked();

    void on_remove_qnt_clicked();

    void on_back_11_clicked();

    void on_back_12_clicked();

    void on_back_13_clicked();

    void on_back_14_clicked();

    void on_back_6_clicked();

    void on_back_15_clicked();

    void on_back_16_clicked();

    void on_back_10_clicked();

    void on_back_8_clicked();

    void on_back_9_clicked();

private:
    int openssl = 0 ;
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
    QVector<FormationInfo> formationInfoList;
    QNetworkAccessManager *manager;
    int presence;
    QString entrepreneurName;
    QString instructorName ;
    QString Identrepreneur ;
    QString type;
    QVBoxLayout *formationLayout;
    QVector<FormationWidget *> formationWidgets;
    QVector<FormationData> formationData;
    QByteArray selectedImageData;

};
#endif // MAINWINDOW_H






