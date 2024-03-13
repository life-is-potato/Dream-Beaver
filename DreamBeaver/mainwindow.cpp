#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tri_bar_2->hide() ;
    connect(ui->tableView, &QAbstractItemView::doubleClicked, this, &MainWindow::handleItemDoubleClicked);
    connect(ui->tableView, &QAbstractItemView::clicked, this, &MainWindow::handleItemClicked);
    connect(ui->searchline, &QLineEdit::textChanged, this, &MainWindow::rechercheProjets);
    connect(ui->sort, &QPushButton::clicked, this, &MainWindow::on_sort_clicked);

    ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_4->setModel(s.afficher());
    ui->tri_bar_3->hide() ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_sort_clicked()
{
    ui->tableView->sortByColumn(1, Qt::AscendingOrder);
}
void MainWindow::rechercheProjets(const QString &searchText) {
    ui->tableView->setModel(c->recherche_projet(searchText));
}
void MainWindow::on_pdf_clicked()
{
         QString defaultFileName="tableauxEntrepreneur.pdf";
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf)"));

        if (!filePath.isEmpty()) {
            QFile file(filePath);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::warning(this, tr("Error"), tr("Could not create file."));
                return;
            }
            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(filePath);

            QPainter painter;
            if (!painter.begin(&printer)) {
                QMessageBox::warning(this, tr("Error"), tr("Could not create painter."));
                return;
            }
            int x= 100;
            int y=100;
            int cw= 100;
            int rowHeight = 20;
            QStringList h;
            for (int i = 0; i<h.size(); ++i) {
                painter.drawText(x+i * cw,y,h.at(i));
            }

            // Draw table data
            int nl= ui->tableView->model()->rowCount();
            int nc= ui->tableView->model()->columnCount();
            for (int i=0;i<nl; ++i) {
                for (int j=0; j<nc; ++j) {
                    QString data = ui->tableView->model()->index(i,j).data(Qt::DisplayRole).toString();
                    painter.drawText(x+j*cw,y+(i+1)*rowHeight, data);
                }
            }

            painter.end();

            QMessageBox::information(this, tr("Success"), tr("PDF file saved successfully."));
        }
    }

void MainWindow::handleItemClicked(const QModelIndex &index)
{
    selectedIndex = index;
}
void MainWindow::on_modifyu_clicked()
{
    if (selectedIndex.isValid()) {
        int row = selectedIndex.row();
        int cin = ui->tableView->model()->index(row, 0).data().toInt();
        QString fname = ui->tableView->model()->index(row, 1).data().toString();
        QString lname = ui->tableView->model()->index(row, 2).data().toString();
        QDate birthday = ui->tableView->model()->index(row, 3).data().toDate();
        QString email = ui->tableView->model()->index(row, 5).data().toString();
        int number = ui->tableView->model()->index(row, 4).data().toInt();

        // Populate the fields in the stacked widget with the data of the selected row
        ui->cin_2->setText(QString::number(cin));
        ui->fname_2->setText(fname);
        ui->lname_2->setText(lname);
        ui->birthday_2->setDate(birthday);
        ui->phone_3->setText(QString::number(number));
        ui->email_2->setText(email);
        ui->stackedWidget->setCurrentIndex(2);
    } else {
        qDebug() << "No row selected.";
    }
}
void MainWindow::handleItemDoubleClicked(const QModelIndex &index)
{
    int row = index.row();
    int col=0;
    //takhou cin doubel clickitha
    QVariant currentcin=ui->tableView->model()->data(ui->tableView->model()->index(row,col));
        int cin=currentcin.toInt();
        bool test= c->EffacerClient(cin);
        if (test)
        {
            ui->tableView->model()->removeRow(row);
        } else
        {
            qDebug()<<"Failed deleting the row";
        }
}


void MainWindow::on_add_user_clicked()
{
    QString cinText=ui->cin->text();
    QString fname=ui->fname->text();
    QString lname=ui->lname->text();
    QDate birthday=ui->birthday->date();
    QString email=ui->email->text();
    QString phoneText= ui->phone_2->text();
    QRegularExpression cinRegex("\\d{8}");
    QRegularExpression phoneRegex("\\d{8}");
    QRegularExpression emailRegex("[\\w.-]+@[\\w.-]+\\.\\w+");
    if (!cinRegex.match(cinText).hasMatch()) {
        ui->cin->setText("Invalid CIN");
        ui->fname->clear();
        ui->lname->clear();
        ui->birthday->clear();
        return;
    }
    if (!phoneRegex.match(phoneText).hasMatch()) {
        ui->phone_2->setText("Invalid phone number");
        ui->fname->clear();
        ui->lname->clear();
        ui->birthday->clear();
        return;
    }
    if (!emailRegex.match(email).hasMatch()) {
        ui->email->setText("Invalid email format");
        ui->fname->clear();
        ui->lname->clear();
        ui->birthday->clearMask();
        return;
    }
    int cin=cinText.toInt();
    int number=phoneText.toInt();
    if (c->AjouterClient(cin, birthday, number, fname, lname, email)) {
        ui->cin->clear();
        ui->fname->clear();
        ui->lname->clear();
        ui->email->clear();
        ui->phone_2->clear();
        ui->birthday->clearMask();
        ui->stackedWidget->setCurrentIndex(0);
    }
}
void MainWindow::on_modify_user_clicked()
{
    QString cinText = ui->cin_2->text();
    QString fname = ui->fname_2->text();
    QString lname = ui->lname_2->text();
    QDate birthday = ui->birthday_2->date();
    QString email = ui->email_2->text();
    QString phoneText = ui->phone_3->text();
    QRegularExpression cinRegex("\\d{8}");
    QRegularExpression phoneRegex("\\d{8}");
    QRegularExpression emailRegex("[\\w.-]+@[\\w.-]+\\.\\w+");
    if (!cinRegex.match(cinText).hasMatch()) {
        ui->cin_2->setText("Invalid CIN");
        // Clear other input fields
        ui->fname_2->clear();
        ui->lname_2->clear();
        ui->email_2->clear();
        ui->phone_3->clear();
        ui->birthday_2->clearMask();
        return;
    }

    if (!phoneRegex.match(phoneText).hasMatch()) {
        ui->phone_3->setText("Invalid phone number");
        ui->cin_2->clear();
        ui->fname_2->clear();
        ui->lname_2->clear();
        ui->email_2->clear();
        ui->birthday_2->clearMask();
        return;
    }
    if (!emailRegex.match(email).hasMatch()) {
        ui->email_2->setText("Invalid email format");
        ui->cin_2->clear();
        ui->fname_2->clear();
        ui->lname_2->clear();
        ui->phone_3->clear();
        ui->birthday_2->clearMask();
        return;
    }
    int cin = cinText.toInt();
    int number = phoneText.toInt();
    if (c->Modify_element(cin, birthday, number, fname, lname, email)) {
        ui->cin_2->clear();
        ui->fname_2->clear();
        ui->lname_2->clear();
        ui->email_2->clear();
        ui->phone_3->clear();
        ui->birthday_2->clearMask();
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        qDebug() << "Failed to modify";
    }
}
void MainWindow::on_Users_clicked()
{
   ui->stackedWidget->setCurrentIndex(1) ;
   ui->tableView->setModel(c->afficher());
}
void MainWindow::on_adduser_clicked()
{
    ui->stackedWidget->setCurrentIndex(0) ;
}
//equipements
void MainWindow::on_equipments_clicked()
{
   ui->stackedWidget->setCurrentIndex(5) ;
   ui->tableView_3->setModel(e->afficher());
    }
void MainWindow::on_add_equipment_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3) ;
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
           QString s = QString::number(id);

           ui->stackedWidget->setCurrentIndex(3);
    }
    else {
           QMessageBox::critical(nullptr,"zid thabet","bhim") ;
    }
}

void MainWindow::on_tableView_3_activated(const QModelIndex &index)
{
       int row = index.row();
       QString cinValue = ui->tableView_3->model()->data(ui->tableView->model()->index(row, 0)).toString();
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



void MainWindow::on_search_button_3_clicked()
{
    QString str = ui->search_bar_3->text() ;
    ui->tableView->setModel(e->search_element(str)) ;
}

void MainWindow::on_search_bar_3_textChanged(const QString &arg1)
{
    ui->tableView->setModel(e->search_element(arg1)) ;
 }



void MainWindow::on_tri_2_clicked()
{
    if(!i) {
         ui->tri_bar_2->hide() ;
         i=1 ;
    }
    else {
         ui->tri_bar_2->show() ;
         i=0 ;
    }
}

void MainWindow::on_tri_type_2_clicked()
{
    ui->tableView->setModel(e->tri_by_type()) ;
}



void MainWindow::on_tri_qnt_2_clicked()
{
    ui->tableView->setModel(e->tri_by_quantity()) ;
}

void MainWindow::on_pdf_3_clicked()
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
//sponsors

void MainWindow::on_sponsors_clicked()
{
   ui->stackedWidget->setCurrentIndex(8) ;
   ui->tableView->setModel(s.afficher());
   //clear_chart_widget() ;
   //chart_render() ;
    }

void MainWindow::on_add_spons_clicked()
{
    ui->stackedWidget->setCurrentIndex(6) ;
}

void MainWindow::on_add_spon_clicked()
{
            int id= ui->ID_10->text().toInt();
            QString nom= ui->names->text();
            QString email= ui->types->text();
            int num= ui->nums->text().toInt();
            QString type= ui->types->text();


        sponsors s(id,nom,email,num,type);
            bool test=s.ajouter();

            if (test)

            {
              ui->tableView->setModel(s.afficher());
                QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("ajout affectué\n"
                "Click Cancel to exit."), QMessageBox::Cancel);
                ui->stackedWidget->setCurrentIndex(7);
            }

                QMessageBox::critical(nullptr, QObject::tr("not ok"),

                                      QObject::tr("ajout non affectué.\n"

                                                  "Click Cancel to exit"), QMessageBox::Cancel);

}

void MainWindow::on_modify_spon_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT * FROM SPONSORS WHERE ID= :ID  ");
        query.bindValue(":ID", ui->IDss->text().toInt());
        query.exec();
        model->setQuery(query);

    // Check if the model contains any data before calling delete

        if (model->rowCount() > 0) {

                    int id= ui->IDss->text().toInt();
                    QString nom= ui->names_4->text();
                    QString email= ui->emails_5->text();
                    int num = ui->nums_4->text().toInt();
                    QString type= ui->types_8->text();


            sponsors s(id,nom,email,num,type);

            bool test = s.modifier(id);

            if (test){

            ui->tableView->setModel(s.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),

            QObject::tr("Modification effectué\n"
            "Click Cancel to exit"),QMessageBox::Cancel);
            ui->stackedWidget->setCurrentIndex(0);
            }

            else{

                ui->tableView->setModel(s.afficher());

                QMessageBox::critical(nullptr,QObject::tr("Not OK"),

                                              QObject::tr("Modification non effectué.\n"
                                                          "Clic Cancel to exit."),QMessageBox::Cancel);
            }

        }
        else {

            QMessageBox::critical(nullptr, QObject::tr("ok"),
                                     QObject::tr("le tableau est vide.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel );

        }

}


void MainWindow::on_delete_spon_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        QSqlQuery query;

        query.prepare("SELECT * FROM SPONSORS WHERE ID= :ID  ");
        query.bindValue(":ID", ui->IDss->text().toInt());
        query.exec();

        model->setQuery(query);

        if (model->rowCount() > 0) {

            int id = ui->IDss->text().toInt();

            bool test = s.supprimer(id);

            if (test) {
                QMessageBox::information(nullptr, QObject::tr("ok"),
                                         QObject::tr("Suppression effectuée. \n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tableView->setModel(s.afficher());
                ui->stackedWidget->setCurrentIndex(0);
            }
            else {

                QMessageBox::critical(nullptr, QObject::tr("ok"),
                                         QObject::tr("Suppression no effectuée.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tableView->setModel(s.afficher());
            }
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("ok"),
                                     QObject::tr("identifiant non trouvée!!\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView->setModel(s.afficher());
        }
}



void MainWindow::on_search_button_s_clicked()
{
    //QString str = ui->search_bars->text() ;
    //ui->tableView->setModel(e->search_element(str)) ;
}

void MainWindow::on_search_bars_textChanged(const QString &arg1)
{
    ui->tableView->setModel(s.search_element(arg1)) ;
 }



void MainWindow::on_tris_clicked()
{
    if(!i) {
         ui->tri_bar_3->hide() ;
         i=1 ;
    }
    else {
         ui->tri_bar_3->show() ;
         i=0 ;
    }
}

void MainWindow::on_tri_az_clicked()
{
    ui->tableView->setModel(s.afficheA_Z()) ;
}



void MainWindow::on_tri_za_clicked()
{
    ui->tableView->setModel(s.afficheZ_A()) ;
}
void MainWindow::on_pdfs_clicked()
{

    ui->tableView->setModel(s.afficher());
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

void MainWindow::on_tableView_4_activated(const QModelIndex &index)
{
    int row = index.row();
    QString cinValue = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSORS WHERE ID = :val");
    query.bindValue(":val", cinValue);
    if (query.exec() && query.next()) {
        ui->ID_10->setText(cinValue);
        ui->names->setText(query.value(1).toString());
        ui->types->setText(query.value(2).toString());
        ui->emails->setText(query.value(3).toString());
        ui->nums->setText(query.value(4).toString());
        ui->stackedWidget->setCurrentIndex(9);
    }
}




