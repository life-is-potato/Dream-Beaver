#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tri_bar->hide() ;
    chart_render() ;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_equipments_clicked()
{
   ui->stackedWidget->setCurrentIndex(0) ;
   ui->tableView->setModel(e->afficher());
   clear_chart_widget() ;
   chart_render() ;
    }


void MainWindow::on_equipments_clicked(bool checked)
{
        if (! checked) {
           ui->equipments->setStyleSheet("background: url(:/equip1.svg) no-repeat;"
                                         "background-color:#2A3E46 ;"
                                         "border-radius:10px;"
                                         "padding: 10px 10px 10px 50px;"
                                         "background-origin: content;"
                                         "font-size:13px;"
                                         "color : #4AC7EA ;" );
       }
       else {
           ui->equipments->setStyleSheet("background-color:transparent ;"
                                         "border-radius:10px;"
                                         "padding: 10px 10px 10px 50px;"
                                         "background: url(:/equip2.svg) no-repeat;"
                                         "color:#BFC9D3 ;"
                                         "font-size:13px;"
                                         "background-origin: content;");
       }
}

void MainWindow::on_add_equipment_clicked()
{
    ui->stackedWidget->setCurrentIndex(1) ;
}

void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0) ;
}

void MainWindow::on_add_equip_clicked()
{
    int id = ui->ID->text().toInt();
    QString name = ui->name->text() ;
    int type = ui->type->text().toInt() ;
    int qnt = ui->qnt->text().toInt() ;
    QString disp ;
    QString desc = ui->desc->toPlainText() ;
    if ((ui->checkBox) && !(ui->checkBox_2)){
        disp = "Disponible" ;
    }
    else {
        disp = "Non disponible" ;
    }
    if (e->Add_element(id,name,type,qnt,disp,desc)) {
           QMessageBox::information(nullptr,"okay","jwk mrgl") ;
           ui->ID->clear();
           ui->name->clear();
           ui->desc->clear();
           ui->qnt->clear();
           ui->type->clear();
           ui->checkBox->clearMask();
           ui->checkBox_2->clearMask();
           ui->tableView->setModel(e->afficher());
           chart_render() ;
           ui->stackedWidget->setCurrentIndex(0);
    }
    else {
           QMessageBox::critical(nullptr,"zid thabet","bhim") ;
    }
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
       int row = index.row();
       QString cinValue = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();
       QSqlQuery query;
       query.prepare("SELECT ID,NOM,TYPE,DESCRIPTION,DISPONIBILITE,QNT_STOCK FROM EQUIPEMENTS WHERE ID = :val");
       query.bindValue(":val", cinValue);
       if (query.exec() && query.next()) {
           ui->ID_2->setText(cinValue);
           ui->name_2->setText(query.value(1).toString());
           ui->type_2->setText(query.value(2).toString());
           ui->desc_2->setText(query.value(3).toString());
           if (query.value(4).toString() == "disponible" ) {
                ui->checkBox_4->setCheckState(Qt::Checked);
                ui->checkBox_3->setCheckState(Qt::Unchecked);
           }
           else {
                ui->checkBox_4->setCheckState(Qt::Unchecked);
                ui->checkBox_3->setCheckState(Qt::Checked);
           }
           ui->qnt_2->setText(query.value(5).toString());
           ui->stackedWidget->setCurrentIndex(2);
       }
}


void MainWindow::on_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_modify_clicked()
{
    int id = ui->ID_2->text().toInt();
    QString name = ui->name_2->text() ;
    int type = ui->type_2->text().toInt() ;
    int qnt = ui->qnt_2->text().toInt() ;
    QString disp ;
    if ((ui->checkBox_4->isChecked()) && !(ui->checkBox_3->isChecked())){
        disp = "Disponible" ;
    }
    else {
        disp = "Non disponible" ;
    }
    QString desc = ui->desc_2->toPlainText() ;

            if (e->Modify_element(id,name,type,qnt,disp,desc)) {
                   QMessageBox::information(nullptr,"okay","jwk mrgl") ;
                   ui->tableView->setModel(e->afficher());
                   chart_render() ;
                   ui->stackedWidget->setCurrentIndex(0);
            }
            else {
                   QMessageBox::critical(nullptr,"zid thabet","8alet") ;
            }

}


void MainWindow::on_delete_2_clicked()
{
    int id = ui->ID_2->text().toInt();
    if (e->Delete_element(id)) {
           QMessageBox::information(nullptr,"okay","jwk mrgl") ;
           ui->tableView->setModel(e->afficher());
           ui->stackedWidget->setCurrentIndex(0);
    }
    else {
           QMessageBox::critical(nullptr,"zid thabet","8alet") ;
    }
}



void MainWindow::on_search_button_2_clicked()
{
    QString str = ui->search_bar_2->text() ;
    ui->tableView->setModel(e->search_element(str)) ;
}

void MainWindow::on_search_bar_2_textChanged(const QString &arg1)
{
    ui->tableView->setModel(e->search_element(arg1)) ;
 }



void MainWindow::on_tri_clicked()
{
    if(!i) {
         ui->tri_bar->hide() ;
         i=1 ;
    }
    else {
         ui->tri_bar->show() ;
         i=0 ;
    }
}

void MainWindow::on_tri_type_clicked()
{
    ui->tableView->setModel(e->tri_by_type()) ;
}



void MainWindow::on_tri_qnt_clicked()
{
    ui->tableView->setModel(e->tri_by_quantity()) ;
}

void MainWindow::on_pdf_clicked()
{

    QString defaultFileName = "walhzi.pdf";
    QString saveFilePath = QFileDialog::getSaveFileName(this, tr("Export PDF"), QDir::homePath() + "/" + defaultFileName, tr("PDF Files (*.pdf)"));

    if (!saveFilePath.isEmpty()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFileName(saveFilePath);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFormat(QPrinter::PdfFormat);

        QPainter painter(&printer);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

        QAbstractItemModel* model = ui->tableView->model();

        if (model) {
            int rowCount = model->rowCount();
            int columnCount = model->columnCount();

            QTextDocument doc;
            QTextCursor cursor(&doc) ;
            QString tableHtml = "<table style=\" width: 100%; border: 1px solid black; font-size: 4px;\">";

            tableHtml += "<tr style=\"background-color: #ccc;\">";
            for (int col = 0; col < columnCount ; ++col) { // Exclude the last 2 columns
                QVariant data = model->headerData(col, Qt::Horizontal);
                tableHtml += "<th style=\"border: 1px solid black; padding: 8px;\">" + data.toString() + "</th>";
            }
            tableHtml += "</tr>";
            for (int row = 0; row < rowCount; ++row) {
                tableHtml += "<tr>";
                for (int col = 0; col < columnCount ; ++col) {
                    QModelIndex index = model->index(row, col);
                    QVariant data = model->data(index);
                    tableHtml += "<td style=\"border: 1px solid black; padding: 8px;\">" + data.toString() + "</td>";
                }
                tableHtml += "</tr>";
            }
            tableHtml += "</table>";
            doc.setHtml(tableHtml);
            painter.scale(30.0, 30.0);
            doc.setPageSize(printer.pageRect().size());
            doc.drawContents(&painter);
        }
        painter.end();
    }
}

void MainWindow::clear_chart_widget(){
    QLayout *donutLayout = ui->donut->layout();
    if (donutLayout) {
        QLayoutItem *item;
        while ((item = donutLayout->takeAt(0)) != nullptr) {
            QWidget *widget = item->widget();
            if (widget) {
                delete widget;
            }
            delete item;
        }
    }
}


void MainWindow::chart_render(){
    clear_chart_widget() ;
    QSqlQueryModel *model = new QSqlQueryModel();
   // d.connect() ; // al DB
    model->setQuery("select * from EQUIPEMENTS where TYPE = '1' ");
    int number1 = model->rowCount();
    model->setQuery("select * from EQUIPEMENTS where TYPE = '2' ");
    int number2 = model->rowCount();
    model->setQuery("select * from EQUIPEMENTS where TYPE = '3' ");
    int number3 = model->rowCount();

    QPieSeries *series = new QPieSeries();
    QStringList colors = {"#002F5D", "#8BC1F7", "#0066CC"};
    QStringList labels = {"1", "2", "3"};
    QVector<int> numbers = {number1, number2, number3};
    for (int i = 0; i < 3; ++i)
    {
        QString color = colors.at(i);
        QString label = labels.at(i);
        QPieSlice *slice = new QPieSlice(label, numbers.at(i));
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::black, 1.5));
        slice->setLabelFont(QFont("Arial", 10,QFont::Bold));
        slice->setExploded();
        connect(slice, &QPieSlice::clicked,ui->donut,[slice, series]() {
            if (slice->isExploded()){
                slice->setExploded(false);
            }
            else {
                slice->setExploded();
            }
            for (QPieSlice *otherSlice : series->slices()){
                if (otherSlice != slice) {
                    otherSlice->setExploded(false);
                }
            }
        });

        slice->setBrush(QColor(color));
        series->append(slice);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->setFont(QFont("Arial", 10));
    chart->setBackgroundBrush(QColor("#FFFFFF")); // Couleur de fond
    QChart::AnimationOptions options = QChart::AllAnimations;
    chart->setAnimationOptions(options);
    chart->legend()->hide();

    chart->setTitle("Type Chart :");

    // 7eslet :
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitleFont(QFont("MS Shell Dlg 2", 10,QFont::Bold));
    chartView->resize(300, 300);

    ui->donut->layout()->addWidget(chartView);
}

void MainWindow::bar_code(QString str) {

}



void MainWindow::on_pushButton_clicked()
{
    bar_code("123456789") ;
}
