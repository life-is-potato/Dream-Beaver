#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabs->setCurrentIndex(0) ;
    ui->projects->setCurrentIndex(0) ;
    ui->tableView_3->setModel(p->afficher()) ;
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);

    QRegExp regex1("^[a-zA-Z]*$");
    QRegExp regex2("^[0-9]*$");

    QValidator *validator1 = new QRegExpValidator(regex1, ui->name);
    QValidator *validator2 = new QRegExpValidator(regex2, ui->qnt);

    ui->name->setValidator(validator1);
    ui->qnt->setValidator(validator2);
    ui->name_2->setValidator(validator1);
    ui->qnt_2->setValidator(validator2);
    ui->ID->setMaxLength(8) ;
    ui->ID->setValidator(validator2) ;



    //api testing :

/*
    QNetworkAccessManager manager;
      QUrl url("https://www.googleapis.com/customsearch/v1?key=AIzaSyDlJTLRZ76Hw_tyGgHQI538SN1S9PN1yl4&cx=064b3bbe8996a4a8d&q=jasser");
      QNetworkRequest request(url);

      QNetworkReply *reply = manager.get(request);
      QEventLoop loop;
      QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
      loop.exec();

      if (reply->error() == QNetworkReply::NoError) {
          QByteArray response = reply->readAll();
          QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
          QJsonObject jsonObject = jsonResponse.object();
          // Parse and handle the JSON response
          qDebug() << jsonObject;
      } else {
          qDebug() << "Error: " << reply->errorString();
      }
*/

}





MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_equipments_clicked()
{
   ui->tabs->setCurrentIndex(1) ;
   ui->tri_bar->hide() ;
   ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->equipments_widget->setCurrentIndex(0) ;
   ui->tableView->setModel(e->afficher());
   clear_chart_widget() ;
   chart_render() ;
    }

void MainWindow::on_add_equipment_clicked()
{
    ui->equipments_widget->setCurrentIndex(1) ;
}

void MainWindow::on_back_clicked()
{
    ui->equipments_widget->setCurrentIndex(0) ;
}

void MainWindow::on_add_equip_clicked()
{
    int id = ui->ID->text().toInt();
    QString name = ui->name->text() ;
    int type = ui->type->currentText().toInt() ;
    int qnt = ui->qnt->text().toInt() ;
    QString desc = ui->desc->toPlainText() ;
    int flag = 0 ;

    if (ui->ID->text().length() != 8 ) {
        flag = 1 ;
        QMessageBox::critical(nullptr,"erreur","ID is not valid ! ") ;
    }

    if (!isAlpha(name)) {
        QMessageBox::critical(nullptr,"erreur","name is not valid !") ;
        flag = 1 ;
    }

    if (!isInteger(qnt)) {
        QMessageBox::critical(nullptr,"erreur","quantité is not valid ! ") ;
        flag = 1 ;
    }

    QString disp ;

    if ((ui->checkBox->isChecked()) && !(ui->checkBox_2->isChecked())){
        disp = "Disponible" ;
    }
    else {
        disp = "Non disponible" ;
    }



if (flag == 0 ){
    if (e->Add_element(id,name,type,qnt,disp,desc)) {
           QMessageBox::information(nullptr,"okay","jwk mrgl") ;
           ui->ID->clear();
           ui->name->clear();
           ui->desc->clear();
           ui->qnt->clear();
           ui->checkBox->clearMask();
           ui->checkBox_2->clearMask();
           ui->tableView->setModel(e->afficher());
           chart_render() ;

           QString s = QString::number(id);

           BarcodePrinter * p = new BarcodePrinter();
           p->configurePrinter();
           p->printBarcode(s);

           ui->equipments_widget->setCurrentIndex(0);
           }
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
           ui->type_2->setCurrentText(query.value(2).toString());
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
           ui->equipments_widget->setCurrentIndex(2);
       }
}


void MainWindow::on_back_2_clicked()
{
    ui->equipments_widget->setCurrentIndex(0);
}

void MainWindow::on_modify_clicked()
{
    int id = ui->ID_2->text().toInt();
    QString name = ui->name_2->text() ;
    int type = ui->type_2->currentText().toInt() ;
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
                   ui->equipments_widget->setCurrentIndex(0);
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
           ui->equipments_widget->setCurrentIndex(0);
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



void MainWindow::on_pushButton_clicked()
{
    QString s = ui->ID_2->text();
    QSqlQuery q;
    q.prepare("SELECT barcode FROM EQUIPEMENTS WHERE ID = :id");
    q.bindValue(":id", s);
    q.exec();

    QString filePath = QFileDialog::getExistingDirectory(this, tr("Select Directory"), QDir::homePath(), QFileDialog::ShowDirsOnly);

    while (q.next()) {
        QByteArray blobData = q.value(0).toByteArray();
        QString fileName = s + ".png";
        QFile file(filePath + "/" + fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "8alet";
        }
        file.write(blobData);
        file.close();

        qDebug() << "Image downloaded mrgl";
    }
}

void MainWindow::on_entreperneurs_clicked()
{
    ui->tabs->setCurrentIndex(2) ;
    ui->entreprneur->setCurrentIndex(0) ;
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setModel(a->afficher()) ;
}


bool MainWindow::isAlpha(QString str ){
    for (QChar c : str) {
           if (!c.isLetter()) {
               return false;
           }
       }
       return true;
}

bool MainWindow::isInteger(int x) {
    QString str = QString::number(x) ;
    for (QChar c : str) {
            if (!c.isDigit()) {
                return false;
            }
        }
        return true;
}



void MainWindow::on_project_clicked()
{
    ui->tabs->setCurrentIndex(0) ;
    ui->projects->setCurrentIndex(0) ;
    ui->tableView_3->setModel(p->afficher()) ;
}

void MainWindow::on_formation_clicked()
{
    ui->tabs->setCurrentIndex(3) ;
    ui->formation_widget->setCurrentIndex(0) ;
    ui->tableView_4->setModel(f->afficher()) ;
    ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::on_adds_clicked()
{
    ui->tabs->setCurrentIndex(4);
    ui->pub_widget->setCurrentIndex(0) ;
    ui->tableView_5->setModel(pu->afficher()) ;
    ui->tableView_5->setSelectionBehavior(QAbstractItemView::SelectRows);
}



void MainWindow::on_add_project_clicked()
{
      ui->projects->setCurrentIndex(1) ;
}

void MainWindow::on_add_projet_clicked()
{
    int id = ui->ID_projet->text().toInt();
    QString name = ui->name_projet->text() ;
    int budget = ui->budget_projet->text().toInt() ;
    int client = ui->client_projet->text().toInt() ;
    QString desc = ui->desc_projet->toPlainText() ;

    p->Add_element(id,name,budget,client,desc) ;
}



void MainWindow::on_tableView_3_activated(const QModelIndex &index)
{
    ui->projects->setCurrentIndex(2) ;
    int row = index.row();
    QString idValue = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 0)).toString();
    QString clientid = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 3)).toString();
    ui->ID_projet_2->setText(idValue) ;
    ui->client_project_2->setText(clientid) ;
}

void MainWindow::on_modify_project_clicked()
{
    int id = ui->ID_projet_2->text().toInt() ;
    QString name = ui->name_projet_2->text() ;
    int budget = ui->budget_project_2->text().toInt() ;
    int client = ui->client_project_2->text().toInt() ;
    QString desc = ui->desc_project_2->toPlainText() ;

    p->Modify_element(id,name,budget,client,desc) ;
    ui->projects->setCurrentIndex(0) ;
    ui->tableView_3->setModel(p->afficher()) ;
}

void MainWindow::on_delete__project_clicked()
{
    int id = ui->ID_projet_2->text().toInt() ;
    p->Delete_element(id) ;
    ui->projects->setCurrentIndex(0) ;
    ui->tableView_3->setModel(p->afficher()) ;
}

void MainWindow::on_add_equipment_2_clicked()
{
    ui->entreprneur->setCurrentIndex(1) ;
}

void MainWindow::on_add_entr_clicked()
{
    int cin = ui->CIN_entr->text().toInt() ;
    QString name = ui->name_entr->text() ;
    QString surname = ui->surname_entr->text();
    QString dob = ui->dob_entr->text() ;
    int number = ui->number_entr->text().toInt() ;
    QString email = ui->email_entr->text() ;

    a->Add_element(cin , name , surname , dob , number , email ) ;
    ui->entreprneur->setCurrentIndex(0) ;
    ui->tableView_2->setModel(a->afficher()) ;

}

void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    ui->entreprneur->setCurrentIndex(2) ;
    int row = index.row();
    QString idValue = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 0)).toString();
    ui->CIN_entr_2->setText(idValue) ;
}

void MainWindow::on_modify_project_2_clicked()
{
    int cin = ui->CIN_entr_2->text().toInt() ;
    QString name = ui->name_entr_2->text() ;
    QString surname = ui->surname_entr_2->text();
    QString dob = ui->dob_entr_2->text() ;
    int number = ui->number_entr_2->text().toInt() ;
    QString email = ui->email_entr_2->text() ;

    a->Modify_element(cin , name , surname , dob , number , email) ;
    ui->entreprneur->setCurrentIndex(0) ;
    ui->tableView_2->setModel(a->afficher()) ;
}

void MainWindow::on_delete__project_2_clicked()
{
    int cin = ui->CIN_entr_2->text().toInt() ;
    a->Delete_element(cin) ;
    ui->entreprneur->setCurrentIndex(0) ;
    ui->tableView_2->setModel(a->afficher()) ;
}

void MainWindow::on_add_equipment_4_clicked()
{
    ui->formation_widget->setCurrentIndex(1) ;
}



void MainWindow::on_add_entr_2_clicked()
{
    int id = ui->id_formation->text().toInt() ;
    int type = ui->type_formation->text().toInt() ;
    QString INSTRUCTEUR = ui->instructor_formation->text() ;
    QString dd = ui->date_d_formation->text() ;
    QString df = ui->date_f_formation->text() ;
    int NB_PARTICIPANTS = ui->nb_participants_formation->text().toInt() ;
    QString DESCRIPTION = ui->desc_formation->toPlainText() ;

    f->Add_element(id,type,INSTRUCTEUR,dd,df,NB_PARTICIPANTS,DESCRIPTION) ;
    ui->formation_widget->setCurrentIndex(0) ;
    ui->tableView_4->setModel(f->afficher()) ;
}

void MainWindow::on_tableView_4_activated(const QModelIndex &index)
{
    ui->formation_widget->setCurrentIndex(2) ;
    int row = index.row();
    QString idValue = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 0)).toString();
    QString type = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 1)).toString();
    QString inst = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 2)).toString();
    QString nb_p = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 5)).toString();
    ui->id_formation_2->setText(idValue) ;
    ui->type_formation_2->setText(type) ;
    ui->instructor_formation_2->setText(inst) ;
    ui->nb_participants_formation_2->setText(nb_p) ;
}

void MainWindow::on_modify_project_3_clicked()
{
    int id = ui->id_formation_2->text().toInt() ;
    int type = ui->type_formation_2->text().toInt() ;
    QString INSTRUCTEUR = ui->instructor_formation_2->text() ;
    QString dd = ui->date_d_formation_2->text() ;
    QString df = ui->date_f_formation_2->text() ;
    int NB_PARTICIPANTS = ui->nb_participants_formation_2->text().toInt() ;
    QString DESCRIPTION = ui->desc_formation_2->toPlainText() ;
    f->Modify_element(id,type,INSTRUCTEUR,dd,df,NB_PARTICIPANTS,DESCRIPTION) ;
    ui->formation_widget->setCurrentIndex(0) ;
    ui->tableView_4->setModel(f->afficher()) ;
}

void MainWindow::on_delete__project_3_clicked()
{
    int id = ui->id_formation_2->text().toInt() ;
    f->Delete_element(id) ;
    ui->formation_widget->setCurrentIndex(0) ;
    ui->tableView_4->setModel(f->afficher()) ;
}

void MainWindow::on_add_equipment_5_clicked()
{
    ui->pub_widget->setCurrentIndex(1) ;
}


void MainWindow::on_add_entr_3_clicked()
{
    int id = ui->id_pub->text().toInt() ;
    QString name = ui->name_pub->text() ;
    int type = ui->type_pub->text().toInt() ;
    int cout = ui->cout_pub->text().toInt() ;
    QString dd = ui->date_d_pub->date().toString("yyyy/MM/dd") ;
    QString df = ui->date_f_pub->date().toString("yyyy/MM/dd") ;
    int prjt_id = ui->prj_id_pub->text().toInt() ;

    pu->Add_element(id,name,type,cout,dd,df,prjt_id) ;
}

void MainWindow::on_tableView_5_activated(const QModelIndex &index)
{
    ui->pub_widget->setCurrentIndex(2) ;
    int row = index.row();
    QString idValue = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 0)).toString();
    QString name = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 1)).toString();
    QString type = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 2)).toString();
    QString cout = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 3)).toString();
    QString dd = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 4)).toString();
    QString df = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 5)).toString();
    QString id_prj = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 6)).toString();

    ui->id_pub_2->setText(idValue) ;
    ui->name_pub_2->setText(name) ;
    ui->type_pub_2->setText(type) ;
    ui->cout_pub_2->setText(cout) ;

    QDate ddDate = QDate::fromString(dd, "yyyy/MM/dd");
    QDate dfDate = QDate::fromString(df, "yyyy/MM/dd");
    qDebug() << df ;
    if (ddDate.isValid() && dfDate.isValid()) {
        ui->date_d_pub_2->setDate(ddDate);
        ui->date_f_pub_2->setDate(dfDate);
    } else {
        // Handle invalid date scenarios (e.g., display an error message)
        qDebug() << "Invalid date format or value!";
    }
    ui->prj_id_pub_2->setText(id_prj) ;
}

void MainWindow::on_modify_pub_clicked()
{
    int id = ui->id_pub_2->text().toInt() ;
    QString name = ui->name_pub_2->text() ;
    int type = ui->type_pub_2->text().toInt() ;
    int cout = ui->cout_pub_2->text().toInt() ;
    QString dd = ui->date_d_pub_2->text() ;
    QString df = ui->date_f_pub_2->text() ;
    int prjt_id = ui->prj_id_pub_2->text().toInt() ;

    pu->Modify_element(id,name,type,cout,dd,df,prjt_id) ;
    ui->pub_widget->setCurrentIndex(0) ;
    ui->tableView_5->setModel(pu->afficher());
}

void MainWindow::on_delete__pub_clicked()
{
   int id = ui->id_pub_2->text().toInt() ;
   pu->Delete_element(id) ;
   ui->pub_widget->setCurrentIndex(0) ;
   ui->tableView_5->setModel(pu->afficher());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->equipments_widget->setCurrentIndex(3) ;
}

void MainWindow::on_search_button_clicked()
{
    // request :
    QString query = ui->search_bar->text();
       QString target_path = "C:\\Users\\jasse\\OneDrive\\Desktop\\under_ground\\target.txt";
       QFile target(target_path);
       if (target.open(QIODevice::WriteOnly | QIODevice::Text))
       {
           QTextStream out(&target);
           out << query;
           target.close();
        }


       //result :
       //result :
       //result :
       QString result_path = "C:\\Users\\jasse\\OneDrive\\Desktop\\under_ground\\results.txt";
       QFile result(result_path);
       if (!result.open(QIODevice::ReadOnly | QIODevice::Text)) {
           // Error handling if file cannot be opened
           qDebug() << "Could not open file for reading";
           return;
       }

       // Wait until the file is not empty
       while (result.size() == 0) {
           QCoreApplication::processEvents(); // Allow processing of events to prevent freezing the UI
       }

       // Create a model to store the data
       QStandardItemModel* model = new QStandardItemModel();
       model->setColumnCount(1);
       model->setHeaderData(0, Qt::Horizontal, "Sites");

       // Read the file line by line
       QTextStream in(&result);
       int row = 0;
       while (!in.atEnd()) {
           QString line = in.readLine();
           QStringList fields = line.split(","); // Assuming CSV format, adjust as needed

           // Add data to the model
           for (int i = 0; i < fields.size(); ++i) {
               QString field = fields.at(i);
               QStandardItem* item = new QStandardItem(field);
               model->setItem(row, i, item);
           }

           row++;
       }
       result.close();

       // Close the file
       result.open(QIODevice::WriteOnly | QIODevice::Truncate);
       result.close();

       // Set the model to the table view
       ui->tableView_6->setModel(model);

       // Adjust column widths
       ui->tableView_6->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);



}
