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


void MainWindow::on_formations_clicked()
{
   ui->stackedWidget->setCurrentIndex(0) ;
   ui->tableView->setModel(e->afficher());
   chart_render() ;
    }



void MainWindow::on_add_formation_clicked()
{
    ui->stackedWidget->setCurrentIndex(1) ;

}

void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0) ;
}

void MainWindow::on_add_form_clicked()
{
    QString idStr = ui->ID_formation->text();
    QRegExp idRegExp("\\b\\d{4,8}\\b");

    if (!idRegExp.exactMatch(idStr)) {
        QMessageBox::critical(nullptr, "Erreur", "ID mahouch howa");
        return;
    }

    int id = idStr.toInt();
    QString type = ui->type_formation->currentText();
    QString instructeur = ui->instructeur->text();
    QDate dateDebut = ui->dateDebut->date();
    QDate dateFin = ui->dateFin->date();
    QString description = ui->description->toPlainText();
    int nbParticipants = ui->nbParticipants->text().toInt();

    if (type.toLower() != "onsite" && type.toLower() != "online") {
        QMessageBox::critical(nullptr, "Erreur", "kifeh ouselt hatitha 5alta!!!???");
        return;
    }

    if (dateDebut < QDate::currentDate()) {
        QMessageBox::critical(nullptr, "Erreur", "tabda fil mathi!!!!???");
        return;
    }

    if (dateFin <= dateDebut) {
        QMessageBox::critical(nullptr, "Erreur", "toufa 9bal ma tabda!!!!????");
        return;
    }

    if (e->Add_element(id, type, instructeur, dateDebut, dateFin, description, nbParticipants)) {
        QMessageBox::information(nullptr, "najhet", "c bon tzedet");
        ui->ID_formation->clear();
        ui->type_formation->setCurrentIndex(0);
        ui->instructeur->clear();
        ui->dateDebut->setDate(QDate::currentDate());
        ui->dateFin->setDate(QDate::currentDate());
        ui->description->clear();
        ui->nbParticipants->clear();
        ui->tableView->setModel(e->afficher());
        ui->stackedWidget->setCurrentIndex(0);
        chart_render();
    } else {
        QMessageBox::critical(nullptr, "Erreur", "fama mochkla");
    }
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    int row = index.row();
        int idValue = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();
        QSqlQuery query;
        query.prepare("SELECT ID,TYPE,INSTRUCTEUR,DD,DF,DESCRIPTION,NB_PARTICIPANTS FROM FORMATIONS WHERE ID = :val");
        query.bindValue(":val", idValue);
        if (query.exec() && query.next()) {
            ui->ID_formation_2->setText(QString::number(idValue));
            ui->type_formation_2->setCurrentText(query.value(1).toString());
            ui->instructeur_2->setText(query.value(2).toString());
            ui->dateDebut_3->setDate(query.value(3).toDate());
            ui->dateFin_3->setDate(query.value(4).toDate());
            ui->description_3->setText(query.value(5).toString());
            ui->nbParticipants_2->setText(QString::number(query.value(6).toInt()));
            ui->stackedWidget->setCurrentIndex(2);
        }
}


void MainWindow::on_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_modify_clicked()
{
    QString idStr = ui->ID_formation_2->text();
    QRegExp idRegExp("\\b\\d{4,8}\\b");

    if (!idRegExp.exactMatch(idStr)) {
        QMessageBox::critical(nullptr, "Erreur", "ID mahouch howa.");
        return;
    }

    int id = idStr.toInt();
    QString type = ui->type_formation_2->currentText();
    QString instructeur = ui->instructeur_2->text();
    QDate dateDebut = ui->dateDebut_3->date();
    QDate dateFin = ui->dateFin_3->date();
    QString description = ui->description_3->toPlainText();
    int nbParticipants = ui->nbParticipants_2->text().toInt();


    if (type.toLower() != "onsite" && type.toLower() != "online") {
        QMessageBox::critical(nullptr, "Erreur", "kifech ouselt hatit type 5alet!!!???");
        return;
    }

    if (dateDebut < QDate::currentDate()) {
        QMessageBox::critical(nullptr, "Erreur", "tabda fil mathi!!!!!?????");
        return;
    }

    if (dateFin <= dateDebut) {
        QMessageBox::critical(nullptr, "Erreur", "toufa 9bal ma tabda!!!????");
        return;
    }

    if (e->Modify_element(id, type, instructeur, dateDebut, dateFin, description, nbParticipants)) {
        QMessageBox::information(nullptr, "mrigel", "tbadlet");
        ui->tableView->setModel(e->afficher());
        ui->stackedWidget->setCurrentIndex(0);
        chart_render();
    } else {
        QMessageBox::critical(nullptr, "Erreur", "fama mochkla.");
    }
}


void MainWindow::on_delete_2_clicked()
{
    int id = ui->ID_formation_2->text().toInt();
        if (e->Delete_element(id)) {
            QMessageBox::information(nullptr, "Opération réussie", "La formation a été supprimée avec succès.");
            ui->tableView->setModel(e->afficher());
            ui->stackedWidget->setCurrentIndex(0);
               chart_render() ;
        } else {
            QMessageBox::critical(nullptr, "Erreur", "Une erreur s'est produite lors de la suppression de la formation.");
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
    int columnIndex = -1;
    for (int i = 0; i < ui->tableView->model()->columnCount(); ++i) {
        if (ui->tableView->model()->headerData(i, Qt::Horizontal).toString() == "DD") {
            columnIndex = i;
            break;
        }
    }

    if (columnIndex != -1) {
        Qt::SortOrder currentOrder = ui->tableView->horizontalHeader()->sortIndicatorOrder();
        Qt::SortOrder newOrder = (currentOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

        ui->tableView->sortByColumn(columnIndex, newOrder);
    } else {
        qDebug() << "mafamech: DD";
    }

}



void MainWindow::on_tri_nbr_clicked()
{
    int columnIndex = -1;
    QString targetColumn = "NB_PARTICIPANTS";

    for (int i = 0; i < ui->tableView->model()->columnCount(); ++i) {
        if (ui->tableView->model()->headerData(i, Qt::Horizontal).toString() == targetColumn) {
            columnIndex = i;
            break;
        }
    }

    if (columnIndex != -1) {
        Qt::SortOrder currentOrder = ui->tableView->horizontalHeader()->sortIndicatorOrder();
        Qt::SortOrder newOrder = (currentOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

        ui->tableView->sortByColumn(columnIndex, newOrder);
    } else {
        qDebug() << "mafamech:" << targetColumn;
    }
}


void MainWindow::on_pdf_clicked()
{
    QString defaultFileName = "formation.pdf";
    QString saveFilePath = QFileDialog::getSaveFileName(this, tr("Export PDF"), QDir::homePath() + "/" + defaultFileName, tr("PDF Files (*.pdf)"));

    if (!saveFilePath.isEmpty()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFileName(saveFilePath);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFormat(QPrinter::PdfFormat);

        QPainter painter(&printer);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

        QAbstractItemModel *model = ui->tableView->model();

        if (model) {
            int rowCount = model->rowCount();
            int columnCount = model->columnCount();

            QTextDocument doc;
            QTextCursor cursor(&doc);
            QString tableHtml = "<table style=\" width: 100%; border: 1px solid black; font-size: 4px;\">";

            tableHtml += "<tr style=\"background-color: #ccc;\">";
            for (int col = 0; col < columnCount; ++col) {
                QVariant data = model->headerData(col, Qt::Horizontal);
                tableHtml += "<th style=\"border: 1px solid black; padding: 8px;\">" + data.toString() + "</th>";
            }
            tableHtml += "</tr>";
            for (int row = 0; row < rowCount; ++row) {
                tableHtml += "<tr>";
                for (int col = 0; col < columnCount; ++col) {
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
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM FORMATIONS WHERE TYPE like 'Onsite'");
    int number1 = model->rowCount();

    model->setQuery("SELECT * FROM FORMATIONS WHERE TYPE like 'Online'");
    int number2 = model->rowCount();

    QPieSeries *series = new QPieSeries();
    QStringList colors = {"#002F5D", "#8BC1F7"};
    QStringList labels = {"Onsite", "Online"};
    QVector<int> numbers =  {number1, number2};
    for (int i = 0; i < 2; ++i)
    {
        QString color = colors.at(i);
        QString label = labels.at(i);
        QPieSlice *slice = new QPieSlice(label, numbers.at(i));
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::black, 1.5));
        slice->setLabelFont(QFont("Arial", 7,QFont::Bold));
        //slice->setExploded();
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
    chart->setBackgroundBrush(QColor("#FFFFFF"));
    QChart::AnimationOptions options = QChart::AllAnimations;
    chart->setAnimationOptions(options);
    chart->legend()->hide();

    chart->setTitle("Stats :");

    // 7eslet :
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitleFont(QFont("MS Shell Dlg 2",10,QFont::Bold));
    chartView->resize(300, 300);
    clear_chart_widget() ;

    ui->donut->layout()->addWidget(chartView);

}

