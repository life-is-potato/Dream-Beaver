#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     //setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);
    ui->tabs->setCurrentIndex(0) ;

    QRegExp regex1("^[a-zA-Z]*$");
    QRegExp regex2("^[a-zA-Z0-9]*$");

    QValidator *validator1 = new QRegExpValidator(regex1, ui->name);
    QValidator *validator2 = new QRegExpValidator(regex2, ui->qnt);

    ui->name->setValidator(validator1);
    ui->qnt->setValidator(validator2);
    ui->name_2->setValidator(validator1);
    ui->qnt_2->setValidator(validator2);
    ui->ID->setMaxLength(8) ;
    ui->ID->setValidator(validator2) ;

    connect(ui->tableView_2, &QAbstractItemView::doubleClicked, this, &MainWindow::handleItemDoubleClicked);
    connect(ui->tableView_2, &QAbstractItemView::clicked, this, &MainWindow::handleItemClicked);
    connect(ui->sortuser, &QPushButton::clicked, this, &MainWindow::on_sortuser_clicked);
    connect(ui->search_bar_3, &QLineEdit::textChanged, this, &MainWindow::rechercheProjets);
    connect(ui->police1, &QToolButton::clicked, this, &MainWindow::setArial);
    connect(ui->police2, &QToolButton::clicked, this, &MainWindow::setTimes);
    connect(ui->red, &QToolButton::clicked, this, &MainWindow::setred);
    connect(ui->green, &QToolButton::clicked, this, &MainWindow::setgreen);
    connect(ui->yellow, &QToolButton::clicked, this, &MainWindow::setyellow);
    connect(ui->blue, &QToolButton::clicked, this, &MainWindow::setblue);
    connect(ui->white, &QToolButton::clicked, this, &MainWindow::setwhite);
    connect(ui->black, &QToolButton::clicked, this, &MainWindow::setblack);
    connect(ui->size, SIGNAL(valueChanged(int)), this, SLOT(size(int)));
    connect(ui->left,&QPushButton::clicked, this, &MainWindow::on_left_clicked);
    connect(ui->right,&QPushButton::clicked, this, &MainWindow::on_right_clicked);
    connect(ui->center, &QPushButton::clicked, this, &MainWindow::on_center_clicked);


    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tri_bar_formation->hide() ;
    chart_render3() ;

    ui->tableView_5->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_5->setModel(s.afficher());
    ui->tri_bar_s->hide() ;
    chart_render4() ;

    ui->tableView_6->setSelectionBehavior(QAbstractItemView::SelectRows);

    int flag = ard.connect_arduino() ;
    if (!flag){
        qDebug() << "arduino mrgl !" ;
    }
    QObject::connect(ard.getserial(),SIGNAL(readyRead()),this,SLOT(checkRFIDCard()));
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
    QString id = ui->ID->text();
    QString name = ui->name->text() ;
    int type = ui->type->currentText().toInt() ;
    int qnt = ui->qnt->text().toInt() ;
    QString desc = ui->desc->toPlainText() ;
    int flag = 0 ;

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

           BarcodePrinter * p = new BarcodePrinter();
           p->configurePrinter();
           p->savebarcode(id) ;

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
    QString id = ui->ID_2->text();
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
    QString id = ui->ID_2->text();
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
void MainWindow::clear_chart_widget2(){
    QLayout *donutLayout = ui->donut_2->layout();
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
    clear_chart_widget();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from EQUIPEMENTS where TYPE = '1'");
    int number1 = model->rowCount();
    model->setQuery("select * from EQUIPEMENTS where TYPE = '2'");
    int number2 = model->rowCount();
    model->setQuery("select * from EQUIPEMENTS where TYPE = '3'");
    int number3 = model->rowCount();

    QPieSeries *series = new QPieSeries();
    QStringList colors = {"#002F5D", "#8BC1F7", "#0066CC"};
    QStringList labels = {"1", "2", "3"};
    QVector<int> numbers = {number1, number2, number3};
    int totalCount = number1 + number2 + number3; // Total count of all slices

    for (int i = 0; i < 3; ++i)
    {
        QString color = colors.at(i);
        QString label = labels.at(i);
        int count = numbers.at(i);
        int percentage = static_cast<int>((count * 100.0) / totalCount);

        // Create slice with label including percentage
        QString labelText = QString("%1\n(%2%)").arg(label).arg(QString::number(percentage));
        QPieSlice *slice = new QPieSlice(labelText, count);
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
    chartView->chart()->setTitleFont(QFont("MS Shell Dlg 2",10,QFont::Bold));
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

    while (q.next()) {

        BarcodePrinter *printer = new BarcodePrinter();
        printer->configurePrinter();
        printer->printBarcode(s);
        qDebug() << "BarCode downloaded mrgl";
    }
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
//entrepreneur
void MainWindow::on_entreperneurs_clicked()
{
    ui->toolbar_3->hide();
    ui->toolbar_2->hide();
    ui->toolbar->hide();
    ui->tabs->setCurrentIndex(2) ;
    ui->entreprneur->setCurrentIndex(0) ;
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setModel(a->afficher()) ;
    clear_chart_widget2() ;
    chart_render2();
    ui->points->clear();
    selectedIndex = QModelIndex();
}
void MainWindow::on_alignement_clicked(){
    if (ui->toolbar_3->isVisible())
    {
        ui->toolbar_3->hide();
    }else
        ui->toolbar_3->show();
}
void MainWindow::on_edit_clicked()
{
    if (ui->toolbar->isVisible())
    {
        ui->toolbar->hide();
    }else
        ui->toolbar->show();
}
void MainWindow::on_file_clicked()
{
    if (ui->toolbar_2->isVisible())
    {
        ui->toolbar_2->hide();
    }else
        ui->toolbar_2->show();
}
void MainWindow::setArial() {
    currentFont.setFamily("Arial");
    applyCurrentFormat();
}

void MainWindow::setTimes() {
    currentFont.setFamily("Times New Roman");
    applyCurrentFormat();
}

void MainWindow::size(int n) {
    currentFont.setPointSize(n);
    applyCurrentFormat();
}

void MainWindow::applyCurrentFormat() {
    QTextCursor cursor = ui->textEdit->textCursor();
    currentFormat.setForeground(currentColor);
    currentFormat.setFont(currentFont);
    cursor.setCharFormat(currentFormat);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::handleItemClicked(const QModelIndex &index)
{
    selectedIndex = index;
    if (selectedIndex.isValid()){

    QString cin = selectedIndex.sibling(selectedIndex.row(), 0).data(Qt::DisplayRole).toString();
    QString points = a->getPoints(cin);
    ui->points->setText(points);}else
            ui->points->clear();
}
void MainWindow::on_deleteu_clicked()
{
    if (selectedIndex.isValid()) {
        int col=0;
        int row = selectedIndex.row();
        QVariant currentcin = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, col));
        // Check if the QVariant holds a valid integer value
        if (currentcin.isValid() && currentcin.canConvert<int>()) {
            int cin=currentcin.toInt();
            bool test=a->Delete_element(cin);

            if (test) {
                ui->tableView_2->model()->removeRow(row);
            } else {
                qDebug() << "failed deleting the row";
            }
    } else {
        qDebug() << "No row selected.";
    }
}
}
void MainWindow::handleItemDoubleClicked(const QModelIndex &index)
{

    int row=index.row();
    int cin = ui->tableView_2->model()->index(row, 0).data().toInt();
    QString fname = ui->tableView_2->model()->index(row, 1).data().toString();
    QString lname = ui->tableView_2->model()->index(row, 2).data().toString();
    QDate birthday = ui->tableView_2->model()->index(row, 3).data().toDate();
    QString email = ui->tableView_2->model()->index(row, 5).data().toString();
    int number = ui->tableView_2->model()->index(row, 4).data().toInt();
    ui->cin2->setText(QString::number(cin));
    ui->fname2->setText(fname);
    ui->lname2->setText(lname);
    ui->birthday2->setDate(birthday);
    ui->phone2->setText(QString::number(number));
    ui->email2->setText(email);
    ui->entreprneur->setCurrentIndex(1);

}
void MainWindow::on_sortuser_clicked()
{
    ui->tableView_2->sortByColumn(1, Qt::AscendingOrder);
}
void MainWindow::rechercheProjets(const QString &searchText) {
    ui->tableView_2->setModel(a->recherche_projet(searchText));
}
void MainWindow::on_pdf_2_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf)"));
    if (filePath.isEmpty()) {
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not create file"));
        return;
    }
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(filePath);
    QTextDocument doc;
    doc.setPlainText(ui->textEdit->toPlainText());
    doc.print(&printer);
    QMessageBox::information(this, tr("Success"), tr("PDF file saved successfuly"));
}
void MainWindow::on_txt_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save as TXT"), "", tr("Text Files (*.txt)"));
    if (filePath.isEmpty()) {
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not create file"));
        return;
    }
    QString doc=ui->textEdit->toPlainText();
    QTextStream out(&file);
    out<<doc;
    file.close();
    QMessageBox::information(this, tr("sahit"), tr("tssajel"));
}

void MainWindow::on_pdfuser_clicked()
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


            // Draw table data
            int nl= ui->tableView_2->model()->rowCount();
            int nc= ui->tableView_2->model()->columnCount();
            for (int i=0;i<nl; ++i) {
                for (int j=0; j<nc; ++j) {
                    QString data = ui->tableView_2->model()->index(i,j).data(Qt::DisplayRole).toString();
                    painter.drawText(x+j*cw,y+(i+1)*rowHeight, data);
                }
            }

            painter.end();

            QMessageBox::information(this, tr("Success"), tr("PDF file saved successfully"));
        }
    }

void MainWindow::on_add_user_clicked()
{
    QString cinText=ui->cin->text();
    QString fname=ui->fname->text();
    QString lname=ui->lname->text();
    QDate birthday=ui->birthday->date();
    QString email=ui->email->text();
    QString phoneText= ui->phone->text();
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
        ui->phone->setText("Invalid phone number");
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
    if (a->Add_element(cin,email,birthday , number , fname, lname)) {
        ui->cin->clear();
        ui->fname->clear();
        ui->lname->clear();
        ui->email->clear();
        ui->phone->clear();
        ui->birthday->clearMask();
        ui->entreprneur->setCurrentIndex(0);
    }

    ui->tableView_2->setModel(a->afficher()) ;
}
void MainWindow::on_modifyuser_clicked()
{
    QString cinText = ui->cin2->text();
    QString fname = ui->fname2->text();
    QString lname = ui->lname2->text();
    QDate birthday = ui->birthday2->date();
    QString email = ui->email2->text();
    QString phoneText = ui->phone2->text();
    QRegularExpression cinRegex("\\d{8}");
    QRegularExpression phoneRegex("\\d{8}");
    QRegularExpression emailRegex("[\\w.-]+@[\\w.-]+\\.\\w+");
    if (!cinRegex.match(cinText).hasMatch()) {
        ui->cin2->setText("Invalid CIN");
        // Clear other input fields
        ui->fname2->clear();
        ui->lname2->clear();
        ui->email2->clear();
        ui->phone2->clear();
        ui->birthday2->clearMask();
        return;
    }

    if (!phoneRegex.match(phoneText).hasMatch()) {
        ui->phone2->setText("Invalid phone number");
        ui->cin2->clear();
        ui->fname2->clear();
        ui->lname2->clear();
        ui->email2->clear();
        ui->birthday2->clearMask();
        return;
    }
    if (!emailRegex.match(email).hasMatch()) {
        ui->email2->setText("Invalid email format");
        ui->cin2->clear();
        ui->fname2->clear();
        ui->lname2->clear();
        ui->phone2->clear();
        ui->birthday2->clearMask();
        return;
    }
    int cin = cinText.toInt();
    int number = phoneText.toInt();
    if (a->Modify_element(cin,email,birthday , number , fname, lname)) {
        ui->cin2->clear();
        ui->fname2->clear();
        ui->lname2->clear();
        ui->email2->clear();
        ui->phone2->clear();
        ui->birthday2->clearMask();
        ui->entreprneur->setCurrentIndex(0);
    } else {
        qDebug() << "Failed to modify";
    }
    ui->tableView_2->setModel(a->afficher()) ;
}

void MainWindow::on_adduser_clicked()
{
    ui->entreprneur->setCurrentIndex(2) ;
}
void MainWindow::chart_render2() {
    clear_chart_widget2();
    QSqlQuery query;
    query.prepare("SELECT DDN FROM ENTREPRENEURS");
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    int number1 = 0;
    int number2 = 0;
    int number3 = 0;
    int totalCount = 0;
    QDate currentDate = QDate::currentDate();
    while (query.next()) {
        QDate birthDate = query.value(0).toDate();
        int age = birthDate.isNull() ? 0 : currentDate.year() - birthDate.year();
        if (age >= 18 && age <= 30)
            number1++;
        else if (age > 30 && age <= 40)
            number2++;
        else if (age > 40)
            number3++;
        totalCount++;
    }
    QPieSeries *series = new QPieSeries();
    QPieSlice *slice1 = series->append("18-30", number1);
    QPieSlice *slice2 = series->append("30-40", number2);
    QPieSlice *slice3 = series->append("over40", number3);
    // Create chart and set series
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Age Pie");
    chart->legend()->setVisible(true);
    chart->legend()->setFont(QFont("MS Shell Dig2", 7));
    chart->setBackgroundBrush(QColor("#FFFFFF"));
    chart->setAnimationOptions(QChart::AllAnimations);
    // Set labels
    slice1->setLabel(QString("18-30   %1%").arg((static_cast<double>(number1) / totalCount) * 100, 0, 'f', 2));
    slice2->setLabel(QString("30-40   %1%").arg((static_cast<double>(number2) / totalCount) * 100, 0, 'f', 2));
    slice3->setLabel(QString("over40  %1%").arg((static_cast<double>(number3) / totalCount) * 100, 0, 'f', 2));
    // nessnaa f chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    connect(series, &QPieSeries::clicked, this, &MainWindow::handleSliceClicked);
    // ncleari layout kdim
    if (ui->donut_2->layout()) {
        QLayoutItem *child;
        while ((child = ui->donut_2->layout()->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        delete ui->donut_2->layout();
    }

    // Set new layout
    QVBoxLayout *layout = new QVBoxLayout(ui->donut_2);
    layout->addWidget(chartView);
}


void MainWindow::on_left_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_right_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_center_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}
void MainWindow::handleSliceClicked(QPieSlice *slice) {
    slice->setExploded();
    slice->setLabelVisible(true);
}
void MainWindow::setred() {
    currentColor = Qt::red;
    applyCurrentFormat();
}

void MainWindow::setgreen() {
    currentColor = Qt::green;
    applyCurrentFormat();
}

void MainWindow::setblue() {
    currentColor = Qt::blue;
    applyCurrentFormat();
}

void MainWindow::setyellow() {
    currentColor = Qt::yellow;
    applyCurrentFormat();
}

void MainWindow::setblack() {
    currentColor = Qt::black;
    applyCurrentFormat();
}
void MainWindow::setwhite() {
    currentColor = Qt::white;
    applyCurrentFormat();
}
void MainWindow::on_pointsbutton_clicked() {
if(selectedIndex.isValid()){
    QString cin = selectedIndex.sibling(selectedIndex.row(), 0).data(Qt::DisplayRole).toString();
    ui->achivement1->setChecked(false);
    ui->achivement2->setChecked(false);
    ui->achivement3->setChecked(false);
    ui->achivement4->setChecked(false);
    ui->achivement5->setChecked(false);
    loadAchivements(cin);
    int p=a->getPoints(cin).toInt() ;
    ui->tableView_4->setModel(a->afficherformation());
    ui->entreprneur->setCurrentIndex(3);
    ui->namee->setText(cin);
    ui->points_2->setText(QString::number(p));
    ui->namee->setReadOnly(true);
    ui->points_2->setReadOnly(true);}
}
void MainWindow::on_savecheck_clicked() {
    if (!selectedIndex.isValid()) {
        QMessageBox::critical(this, "Error", "No item selected.");
        return;
    }

    QString cinToFind = selectedIndex.sibling(selectedIndex.row(), 0).data(Qt::DisplayRole).toString();
    QFile file("checkbox_states.txt");

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading and writing.";
        QMessageBox::critical(this, "Error", "Failed to open file for reading and writing.");
        return;
    }

    QStringList allLines;
    QTextStream in(&file);

    // Read existing data
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");
        if (parts.size() == 3 && parts[2] == cinToFind) {
            // Skip the line if the cin is found
            continue;
        }
        allLines.append(line);
    }

    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing.";
        QMessageBox::critical(this, "Error", "Failed to open file for writing.");
        return;
    }

    QTextStream out(&file);

    // Write all remaining lines back to the file
    for (const QString& line : allLines) {
        out << line << endl;
    }

    // Append new data as if the cin is not found
    for (int i = 1; i <= 5; ++i) {
        QString checkboxName = "achivement" + QString::number(i);
        QCheckBox* checkbox = ui->widget->findChild<QCheckBox*>(checkboxName);
        if (checkbox) {
            out << checkboxName << " " << (checkbox->isChecked() ? "1" : "0") << " " << cinToFind << endl;
        }
    }

    file.close();
    QMessageBox::information(this, "Success", "Checkboxes saved successfully.");
}






void MainWindow::on_achivement1_clicked(bool checked) {
    if (checked) {
        QString cin = selectedIndex.sibling(selectedIndex.row(), 0).data(Qt::DisplayRole).toString();
        int p=a->getPoints(cin).toInt();
        ui->points_2->setText(QString::number(p));
        QMessageBox::StandardButton r=QMessageBox::question(this, "achievement unlocked", "are you sure you want to unlock this achievement?", QMessageBox::Yes | QMessageBox::No);
        if (r==QMessageBox::Yes)
        {
            a->addPoints(cin,1000);
            p=p+1000;
            ui->points_2->setText(QString::number(p));
            ui->achivement1->setEnabled(false);
        } else
        {
            ui->achivement1->setChecked(false);
        }
    }
}

void MainWindow::on_achivement2_clicked(bool checked) {
    if (checked) {
        QString cin = selectedIndex.sibling(selectedIndex.row(), 0).data(Qt::DisplayRole).toString();
        int p= a->getPoints(cin).toInt();
        ui->points_2->setText(QString::number(p));
        QMessageBox::StandardButton r=QMessageBox::question(this, "achievement Unlocked", "are you sure you want to unlock this achievement?", QMessageBox::Yes | QMessageBox::No);
        if (r==QMessageBox::Yes)
        {
            a->addPoints(cin, 2000);
            p=p+2000;
            ui->points_2->setText(QString::number(p));
            ui->achivement2->setEnabled(false);
        } else
        {
            ui->achivement2->setChecked(false);
        }
    }
}

void MainWindow::on_achivement3_clicked(bool checked) {
    if (checked)
    {
        QString cin = selectedIndex.sibling(selectedIndex.row(), 0).data(Qt::DisplayRole).toString();
        int p=a->getPoints(cin).toInt();
        ui->points_2->setText(QString::number(p));
        QMessageBox::StandardButton r= QMessageBox::question(this, "achievement Unlocked", "are you sure you want to unlock this achievement?", QMessageBox::Yes | QMessageBox::No);
        if (r==QMessageBox::Yes)
        {
            a->addPoints(cin, 1500);
            p=p+1500;
            ui->points_2->setText(QString::number(p));
            ui->achivement3->setEnabled(false);
        } else
        {
            ui->achivement3->setChecked(false);
        }
    }
}

void MainWindow::on_achivement4_clicked(bool checked) {
    if (checked)
    {
        QString cin= selectedIndex.sibling(selectedIndex.row(), 0).data(Qt::DisplayRole).toString();
        int p=a->getPoints(cin).toInt();
        ui->points_2->setText(QString::number(p));
        QMessageBox::StandardButton r= QMessageBox::question(this, "achievement Unlocked", "are you sure you want to unlock this achievement?", QMessageBox::Yes | QMessageBox::No);
        if (r==QMessageBox::Yes)
        {
            a->addPoints(cin, 500);
            p=p+500;
            ui->points_2->setText(QString::number(p));
            ui->achivement4->setEnabled(false);
        } else
        {
            ui->achivement4->setChecked(false);
        }
    }
}

void MainWindow::on_achivement5_clicked(bool checked) {
    if (checked) {
        QString cin= selectedIndex.sibling(selectedIndex.row(), 0).data(Qt::DisplayRole).toString();
        int p=a->getPoints(cin).toInt();
        ui->points_2->setText(QString::number(p));
        QMessageBox::StandardButton r=QMessageBox::question(this, "achievement Unlocked", "are you sure you want to unlock this achievement?", QMessageBox::Yes | QMessageBox::No);
        if (r==QMessageBox::Yes) {
            a->addPoints(cin, 2500);
            p =p+2500;
            ui->points_2->setText(QString::number(p));
            ui->achivement5->setEnabled(false);
        } else {
            ui->achivement5->setChecked(false);
        }
    }
}

void MainWindow::loadAchivements(QString cin)
{
    QFile file("checkbox_states.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading.";
        return;
    }
    QTextStream in(&file);
    bool cinFound = false; // Flag to track if cin is found
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");
        if (parts.size() == 3) {
            QString checkboxName = parts[0];
            bool isChecked = parts[1].toInt();
            QString cinf = parts[2];
            if (cinf == cin) {
                QCheckBox* checkbox = ui->widget->findChild<QCheckBox*>(checkboxName);
                if (checkbox) {
                    checkbox->setChecked(isChecked);
                    checkbox->setEnabled(isChecked == 0); // Enable checkbox if isChecked is 0
                }
                cinFound = true; // Set flag to true
            }
        }
    }
    file.close();

    // If cin is not found, enable all checkboxes
    if (!cinFound) {
        for (int i = 1; i <= 5; ++i) {
            QString checkboxName = "achivement" + QString::number(i);
            QCheckBox* checkbox = ui->widget->findChild<QCheckBox*>(checkboxName);
            if (checkbox) {
                checkbox->setEnabled(true);
            }
        }
    }
}


void MainWindow::on_adduserfor_clicked() {
    QString cin= ui->namee->text();
    QString idf = ui->f_id->text();
    if (a->addFreeFormation(cin, idf)) {
        a->losePoints(cin,1000);
        QMessageBox::information(this,"success","user added succesfuly");
        QString points =a->getPoints(cin);
        ui->points_2->setText(points);
    } else {
        QMessageBox::warning(this,"error","failed to add user");
    }
}
//formation
void MainWindow::on_formation_clicked()
{
    ui->tabs->setCurrentIndex(3) ;
   ui->formations->setCurrentIndex(0) ;
   ui->tableView_3->setModel(f->afficher());
   chart_render3() ;
   connect(ui->calendarFomation_2, &QCalendarWidget::clicked, this, &MainWindow::on_calendarWidget_clicked);

   populateCalendarWithFormations();
       manager = new QNetworkAccessManager(this);
       connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::replyFinished);
    }
void MainWindow::on_add_formation_clicked()
{
    ui->formations->setCurrentIndex(1) ;

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

    if (f->Add_element(id, type, instructeur, dateDebut, dateFin, description, nbParticipants,selectedImageData)) {
        QMessageBox::information(nullptr, "najhet", "c bon tzedet");
        ui->ID_formation->clear();
        ui->type_formation->setCurrentIndex(0);
        ui->instructeur->clear();
        ui->dateDebut->setDate(QDate::currentDate());
        ui->dateFin->setDate(QDate::currentDate());
        ui->description->clear();
        ui->nbParticipants->clear();
        ui->tableView_3->setModel(f->afficher());
        ui->formations->setCurrentIndex(0);
        chart_render3();
    } else {
        QMessageBox::critical(nullptr, "Erreur", "fama mochkla");
    }
}


void MainWindow::on_tableView_3_activated(const QModelIndex &index)
{
    int row = index.row();
        int idValue = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 0)).toInt();
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
            ui->formations->setCurrentIndex(2);
        }
}

void MainWindow::on_modify_formation_clicked()
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

    if (f->Modify_element(id, type, instructeur, dateDebut, dateFin, description, nbParticipants,selectedImageData)) {
        QMessageBox::information(nullptr, "mrigel", "tbadlet");
        ui->tableView_3->setModel(f->afficher());
        ui->formations->setCurrentIndex(0);
        chart_render();
    } else {
        QMessageBox::critical(nullptr, "Erreur", "fama mochkla.");
    }
}


void MainWindow::on_delete_formation_clicked()
{
    int id = ui->ID_formation_2->text().toInt();
        if (f->Delete_element(id)) {
            QMessageBox::information(nullptr, "Opération réussie", "La formation a été supprimée avec succès.");
            ui->tableView_3->setModel(f->afficher());
            ui->formations->setCurrentIndex(0);
               chart_render() ;
        } else {
            QMessageBox::critical(nullptr, "Erreur", "Une erreur s'est produite lors de la suppression de la formation.");
        }
}



void MainWindow::on_search_button_f_clicked()
{
    QString str = ui->search_bar_2->text() ;
    ui->tableView_3->setModel(f->search_element(str)) ;
}

void MainWindow::on_search_formation_textChanged(const QString &arg1)
{
    ui->tableView_3->setModel(f->search_element(arg1)) ;
 }



void MainWindow::on_tri_formation_clicked()
{
    if(!i) {
         ui->tri_bar_formation->hide() ;
         i=1 ;
    }
    else {
         ui->tri_bar_formation->show() ;
         i=0 ;
    }
}

void MainWindow::on_tri_typefor_clicked()
{
    int columnIndex = -1;
    for (int i = 0; i < ui->tableView_3->model()->columnCount(); ++i) {
        if (ui->tableView_3->model()->headerData(i, Qt::Horizontal).toString() == "DD") {
            columnIndex = i;
            break;
        }
    }

    if (columnIndex != -1) {
        Qt::SortOrder currentOrder = ui->tableView_3->horizontalHeader()->sortIndicatorOrder();
        Qt::SortOrder newOrder = (currentOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

        ui->tableView_3->sortByColumn(columnIndex, newOrder);
    } else {
        qDebug() << "mafamech: DD";
    }

}



void MainWindow::on_tri_nbrfor_clicked()
{
    int columnIndex = -1;
    QString targetColumn = "NB_PARTICIPANTS";

    for (int i = 0; i < ui->tableView_3->model()->columnCount(); ++i) {
        if (ui->tableView_3->model()->headerData(i, Qt::Horizontal).toString() == targetColumn) {
            columnIndex = i;
            break;
        }
    }

    if (columnIndex != -1) {
        Qt::SortOrder currentOrder = ui->tableView_3->horizontalHeader()->sortIndicatorOrder();
        Qt::SortOrder newOrder = (currentOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

        ui->tableView_3->sortByColumn(columnIndex, newOrder);
    } else {
        qDebug() << "mafamech:" << targetColumn;
    }
}


void MainWindow::on_pdf_formation_clicked()
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


void MainWindow::clear_chart_widget3(){
    QLayout *donutLayout = ui->donut_5->layout();
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

void MainWindow::chart_render3(){
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
    clear_chart_widget3() ;

    ui->donut_5->layout()->addWidget(chartView);

}
//sponsors
void MainWindow::on_sponsors_clicked()
{
    ui->tabs->setCurrentIndex(4) ;
    ui->tableView_5->setModel(s.afficher());
    ui->sponsor->setCurrentIndex(3) ;

   clear_chart_widget4() ;
   chart_render() ;
    }

void MainWindow::on_adds_clicked()
{
    ui->sponsor->setCurrentIndex(1) ;
}


void MainWindow::on_add_spon_clicked()
{
    // Récupérer les données saisies par l'utilisateur
    int id = ui->ID_s->text().toInt();
    QString nom = ui->name_s->text();
    QString email = ui->email_s->text();
    int num = ui->num_s->text().toInt();
    QString type = ui->type_s->text();

    // Vérifier si des champs obligatoires sont vides
    if (nom.isEmpty() || email.isEmpty() || type.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Champs obligatoires vides"),
                              QObject::tr("Veuillez remplir tous les champs obligatoires."),
                              QMessageBox::Cancel);
        return; // Arrêter l'exécution de la fonction
    }

    // Vérifier si l'email est valide (vous pouvez ajouter d'autres validations selon vos besoins)
    QRegularExpression re("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
    if (!re.match(email).hasMatch()) {
        QMessageBox::critical(nullptr, QObject::tr("Email invalide"),
                              QObject::tr("Veuillez saisir une adresse email valide."),
                              QMessageBox::Cancel);
        return; // Arrêter l'exécution de la fonction
    }

    // Créer l'objet sponsor avec les données saisies
    sponsors s(id, nom, email, num, type);

    // Ajouter le sponsor
    bool ajoutReussi = s.ajouter();

    // Afficher un message en fonction du résultat de l'ajout
    if (ajoutReussi) {
        ui->tableView_5->setModel(s.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajout réussi"),
                                 QObject::tr("Le sponsor a été ajouté avec succès."),
                                 QMessageBox::Cancel);
        ui->sponsor->setCurrentIndex(2);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Ajout échoué"),
                              QObject::tr("Échec de l'ajout du sponsor."),
                              QMessageBox::Cancel);
    }
}

void MainWindow::on_modify_spon_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT * FROM SPONSORES WHERE ID= :ID  ");
        query.bindValue(":ID", ui->ID_2_s->text().toInt());
        query.exec();
        model->setQuery(query);

    // Check if the model contains any data before calling delete

        if (model->rowCount() > 0) {

            int id= ui->ID_2_s->text().toInt();
                    QString nom= ui->name_2_s->text();
                    QString email= ui->email_2_s->text();
                    int num = ui->num_2_s->text().toInt();
                    QString type= ui->type_2_s->text();


 sponsors s(id,nom,email,num,type);

            bool test = s.modifier(id);

            if (test){
                ui->tableView_5->setModel(s.afficher());
            ui->sponsor->setCurrentIndex(2);
            }

            else{

                ui->tableView_5->setModel(s.afficher());

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

        query.prepare("SELECT * FROM SPONSORES WHERE ID= :ID  ");
        query.bindValue(":ID", ui->ID_2_s->text().toInt());
        query.exec();

        model->setQuery(query);

        if (model->rowCount() > 0) {

            int id = ui->ID_2_s->text().toInt();

            bool test = s.supprimer(id);

            if (test) {
                QMessageBox::information(nullptr, QObject::tr("ok"),
                                         QObject::tr("Suppression effectuée. \n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tableView_5->setModel(s.afficher());
                ui->sponsor->setCurrentIndex(2);
            }
            else {

                QMessageBox::critical(nullptr, QObject::tr("ok"),
                                         QObject::tr("Suppression no effectuée.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tableView_5->setModel(s.afficher());
            }
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("ok"),
                                     QObject::tr("identifiant non trouvée!!\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView_5->setModel(s.afficher());
        }
}



void MainWindow::on_search_button_s_clicked()
{
    QString str = ui->search_bar_s->text() ;
    ui->tableView_5->setModel(s.search_element(str)) ;
}

void MainWindow::on_search_bar_s_textChanged(const QString &arg1)
{
    ui->tableView_5->setModel(s.search_element(arg1)) ;
 }



void MainWindow::on_tri_s_clicked()
{
    if(!i) {
         ui->tri_bar_s->hide() ;
         i=1 ;
    }
    else {
         ui->tri_bar_s->show() ;
         i=0 ;
    }
}

void MainWindow::on_tri_az_clicked()
{
    ui->tableView_5->setModel(s.afficheA_Z()) ;
}



void MainWindow::on_tri_za_clicked()
{
    ui->tableView_5->setModel(s.afficheZ_A()) ;
}





void MainWindow::on_pdf_s_clicked()
{

    ui->tableView_5->setModel(s.afficher());
    QString defaultFileName = "walhzi.pdf";
    QString saveFilePath = QFileDialog::getSaveFileName(this, tr("Export PDF"), QDir::homePath() + "/" + defaultFileName, tr("PDF Files (*.pdf)"));

    if (!saveFilePath.isEmpty()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFileName(saveFilePath);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFormat(QPrinter::PdfFormat);

        QPainter painter(&printer);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

        QAbstractItemModel* model = ui->tableView_5->model();

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

void MainWindow::clear_chart_widget4(){
    QLayout *donutLayout = ui->donut_3->layout();
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


void MainWindow::chart_render4(){
    clear_chart_widget() ;
    QSqlQueryModel *model = new QSqlQueryModel();
   // d.connect() ; // al DB
    model->setQuery("select * from SPONSORS where TYPE = 'morale' ");
    int number1 = model->rowCount();
    model->setQuery("select * from SPONSORS where TYPE = 'physique' ");
    int number2 = model->rowCount();
    QPieSeries *series = new QPieSeries();
    QStringList colors = {"#002F5D", "#8BC1F7"};
    QStringList labels = {"morale", "physique"};
    QVector<int> numbers = {number1, number2};
    for (int i = 0; i < 2; ++i)
    {
        QString color = colors.at(i);
        QString label = labels.at(i);
        QPieSlice *slice = new QPieSlice(label, numbers.at(i));
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::black, 1.5));
        slice->setLabelFont(QFont("Arial", 10,QFont::Bold));
        slice->setExploded();
        connect(slice, &QPieSlice::clicked,ui->donut_3,[slice, series]() {
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

    ui->donut_3->layout()->addWidget(chartView);
}





void MainWindow::on_tableView_5_activated(const QModelIndex &index)
{
    int row = index.row();
    QString cinValue = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 0)).toString();
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSORES WHERE ID = :val");
    query.bindValue(":val", cinValue);
    if (query.exec() && query.next()) {
        ui->ID_2_s->setText(cinValue);
        ui->name_2_s->setText(query.value(1).toString());
        ui->email_2_s->setText(query.value(2).toString());
        ui->num_2_s->setText(query.value(3).toString());
        ui->type_2_s->setText(query.value(4).toString());
        ui->sponsor->setCurrentIndex(0);
    }
}
//projet
void MainWindow::on_project_clicked()
{
    ui->tabs->setCurrentIndex(0) ;
    ui->tableView_6->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->projects->setCurrentIndex(2);
    ui->tableView_6->setModel(p->afficher());
}
void MainWindow::on_add_project_clicked(){
    ui->projects->setCurrentIndex(0);
}
void MainWindow::on_add_projet_clicked(){
    int id=ui->ID_projet->text().toInt();
    float budget=ui->budget_projet->text().toFloat();
     QString desc = ui->desc_projet->toPlainText();
    int client=ui->client_projet->text().toInt();
    QString name=ui->name_projet->text();
    if (p->Add_element(id,name,budget,client, desc)) {
        ui->ID_projet->clear();
        ui->budget_projet->clear();
        ui->desc_projet->clear();
        ui->client_projet->clear();
        ui->name_projet->clear();
        ui->projects->setCurrentIndex(2);
    }
}
void MainWindow::on_delete_project(){
    int id = ui->ID_projet_2->text().toInt();
    if (p->Delete_element(id)) {
           QMessageBox::information(nullptr,"okay","jwk mrgl") ;
           ui->tableView_6->setModel(p->afficher());
           ui->projects->setCurrentIndex(2);
    }
    else {
           QMessageBox::critical(nullptr,"zid thabet","8alet") ;
    }
}
void MainWindow::on_modify_project(){
    int id=ui->ID_projet_2->text().toInt();
    float budget=ui->budget_project_2->text().toFloat();
     QString desc = ui->desc_project_2->toPlainText();
    int client=ui->client_project_2->text().toInt();
    QString name=ui->name_projet_2->text();
    if (p->Modify_element(id,name ,budget ,client ,desc)) {
                   QMessageBox::information(nullptr,"okay","jwk mrgl") ;
                   ui->tableView_6->setModel(e->afficher());
                   ui->projects->setCurrentIndex(2);}
}
void MainWindow::on_tableView_6_activated(const QModelIndex &index){
    int row = index.row();
    QString id = ui->tableView_6->model()->data(ui->tableView_5->model()->index(row, 0)).toString();
    QSqlQuery query;
    query.prepare("SELECT * FROM PROJETS WHERE ID = :val");
    query.bindValue(":val", id);
    if (query.exec() && query.next()) {
        ui->ID_projet_2->setText(id);
        ui->name_2_s->setText(query.value(1).toString());
        ui->budget_project_2->setText(query.value(2).toString());
        ui->client_project_2->setText(query.value(3).toString());
        ui->projects->setCurrentIndex(1);
    }

}

void MainWindow::on_searchengine_clicked()
{
    ui->equipments_widget->setCurrentIndex(3) ;
}

void MainWindow::on_search_btn_clicked()
{
    // request :
    QString query = ui->searchbar->text();
    QString target_path = R"(C:/Users/jasse/Desktop/final/Dream-Beaver/build/target.txt)";
       QFile target(target_path);
       if (target.open(QIODevice::WriteOnly | QIODevice::Text))
       {
           QTextStream out(&target);
           out << query;
           target.close();
        }
       //result :
       QString result_path = R"(C:/Users/jasse/Desktop/final/Dream-Beaver/build/results.txt)";
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
       ui->tableView_7->setModel(model);

       // Adjust column widths
       ui->tableView_7->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

}


void MainWindow::on_arduino_clicked()
{
    ui->equipments_widget->setCurrentIndex(4);

    QTimer *dataMonitorTimer;
    dataMonitorTimer = new QTimer(this);
    connect(dataMonitorTimer, &QTimer::timeout, this, &MainWindow::checkDataChanges);
    dataMonitorTimer->start(1000);

   }

void MainWindow::on_add_s_clicked()
{
    ui->sponsor->setCurrentIndex(1) ;
}


void MainWindow::on_chatbot_send_clicked()
{
    QString botresponse ;
    botresponse = s.chatbot(ui->usermessage->text()) ;
    ui->response->append(botresponse) ;
}

void MainWindow::on_historique_clicked()
{
    ui->sponsor->setCurrentIndex(2) ;
    ui->historique_page->setText(s.historique()) ;
}

void MainWindow::checkDataChanges() {

       QByteArray data = ard.read_from_arduino();

       QString result(data);
       QString new_id ;
       QSqlQuery q;
       QString id ;
       QString name ;
       QString type ;
       QString dispo ;
       int qnt ;
       int y = 0;


       q.prepare("SELECT * FROM EQUIPEMENTS WHERE ID = :id_c");
       q.bindValue(":id_c", result);

       if (q.exec()) {
           while (q.next()) {
               id = q.value(0).toString() ;
               name = q.value(1).toString() ;
               type = q.value(2).toString() ;
               dispo = q.value(3).toString() ;
               qnt = q.value(4).toInt();
               y++;
           }

           if (y > 0 && result != "0") {
               ui->id_storage->setText(id) ;
               ui->name_storage->setText(name) ;
               ui->type_storage->setText(type) ;
               ui->disp_storage->setText(dispo) ;
               ard.write_to_arduino("1") ;
               i = 0;
               // Execute your code here
               QTimer *timer = new QTimer(this);
               connect(timer, &QTimer::timeout, this, [this, qnt]() {
                   ui->storage_ref->setText(QString::number(i));
                   if (++i >= qnt + 1) {
                       static_cast<QTimer*>(sender())->deleteLater();
                   }
               });
               timer->start(30);
           }
           if (result != "" && y == 0 ){
                ui->id_storage->clear() ;
                ui->name_storage->clear() ;
                ui->type_storage->clear() ;
                ui->disp_storage->clear() ;
                ard.write_to_arduino("0") ;
                new_id = result ;
                ui->storage_ref->setText("0") ;
                int result = QMessageBox::question(nullptr, "Entity Not Found", "Want to add it?",
                                                   QMessageBox::Yes | QMessageBox::No);

                if (result == QMessageBox::Yes) {
                    ui->equipments_widget->setCurrentIndex(1) ;
                    ui->ID->setText(new_id) ;
               }
           }
       }
   }

void MainWindow::on_add_qnt_clicked()
{
    int qnt = ui->storage_ref->text().toInt() ;
    int addon = ui->lineEdit->text().toInt() ;
    QString id = ui->id_storage->text() ;
    QString name = ui->name_storage->text() ;

    qDebug() << name;
    int new_qnt = qnt + addon ;
    QSqlQuery q ;
    q.prepare("UPDATE EQUIPEMENTS SET QNT_STOCK = :qnt WHERE  ID = :id ");
    q.bindValue(":qnt",new_qnt) ;
    q.bindValue(":id",id) ;

    if(q.exec()){
        ard.write_to_arduino("Name : " + name.toUtf8()) ;
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->formations->setCurrentIndex(5);
}
void MainWindow::on_pushButton_3_clicked()
{
    ui->formations->setCurrentIndex(0);
}
void MainWindow::on_pushButton_8_clicked() {
    ui->formations->setCurrentIndex(6);
    refreshFormationWidgets();
}

void MainWindow::populateCalendarWithFormations()
{
    ui->calendarFomation_2->setDateTextFormat(QDate(), QTextCharFormat());
    formationInfoList.clear();

    QSqlQuery query;
    query.prepare("SELECT ID, INSTRUCTEUR, DD, DF FROM FORMATIONS");

    if (query.exec())
    {
        while (query.next())
        {
            int id = query.value(0).toInt();
            QString instructeur = query.value(1).toString();
            QDate startDate = query.value(2).toDate();
            QDate endDate = query.value(3).toDate();

            QTextCharFormat startFormat;
            startFormat.setBackground(Qt::blue);
            ui->calendarFomation_2->setDateTextFormat(startDate, startFormat);

            QTextCharFormat endFormat;
            endFormat.setBackground(Qt::red);
            ui->calendarFomation_2->setDateTextFormat(endDate, endFormat);

            FormationInfo info;
            info.id = id;
            info.instructeur = instructeur;
            info.dateDebut = startDate;
            info.dateFin = endDate;
            formationInfoList.append(info);
        }
    }
    else
    {
        qDebug() << "Query failed:" << query.lastError();
    }
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    bool dateFound = false;

    for (const FormationInfo &info : formationInfoList)
    {
        if (date == info.dateDebut || date == info.dateFin)
        {
            QMessageBox::information(this, "Formation Info",
                                     "ID: " + QString::number(info.id) +
                                     "\nINSTRUCTEUR: " + info.instructeur);
            dateFound = true;
            break;
        }
    }

    if (!dateFound && ui->calendarFomation_2->dateTextFormat(date).isEmpty())
    {
        ui->dateDebut->setDate(date);

        ui->formations->setCurrentIndex(1);
    }
}

void MainWindow::checkAbsence()
{
    // Obtenez la date actuelle
    QDate currentDate = QDate::currentDate();
    qDebug() << "Current Date:" << currentDate.toString("yyyy-MM-dd");

    // Préparez la requête SQL pour récupérer les informations pertinentes
    QSqlQuery query;
    query.prepare("SELECT ef.ID_ENTR, ef.ID_FORM, ef.PRESENCE, f.DF "
                  "FROM ENTREPRENEURS_FORMATIONS ef "
                  "INNER JOIN FORMATIONS f ON ef.ID_FORM = f.ID "
                  "WHERE f.DF > :currentDate");
    query.bindValue(":currentDate", currentDate);

    bool emailsSent = false;  // Flag pour suivre si des e-mails ont été envoyés

    if (query.exec()) {
        bool formationsFound = false;  // Flag pour suivre si des formations sont trouvées
        while (query.next()) {
            formationsFound = true;  // Réglez le drapeau sur true si des lignes sont trouvées
            int entrepreneurID = query.value("ID_ENTR").toInt();
            int presence = query.value("PRESENCE").toInt();
            QDate formationDate = query.value("DF").toDate();
            int absence = currentDate.daysTo(formationDate) - presence;

            if (absence > 3) {
                QString entrepreneurEmail = getEmailById(entrepreneurID); // Obtenez l'e-mail de l'entrepreneur
                QString subject = "Absence Notification"; // Objet de l'e-mail
                QString body = "Dear Entrepreneur,\n\n"
                               "This is to inform you that you have been absent from multiple formations. "
                               "Please ensure attendance in upcoming formations.\n\n"
                               "Best regards,\n"
                               "Your Organization"; // Corps de l'e-mail

                // Appel du script Python avec les informations nécessaires
                QProcess *process = new QProcess(this);
                QString pythonScript = "C:/Users/jasse/Desktop/final/Dream-Beaver/mail.py";
                QStringList arguments;
                arguments << entrepreneurEmail << subject << body;
                process->start("python", QStringList() << pythonScript << arguments);
                process->waitForFinished();

                // Vérifier le résultat de l'envoi de l'e-mail
                if (process->exitCode() == 0) {
                    qDebug() << "Sent email to Entrepreneur with ID:" << entrepreneurID;
                    emailsSent = true;  // Réglez le drapeau sur true si l'e-mail a été envoyé
                } else {
                    qDebug() << "Error sending email to Entrepreneur with ID:" << entrepreneurID;
                }
            }
        }

        if (!formationsFound) {
            qDebug() << "No formations found with DF > currentDate";
        }
    } else {
        qDebug() << "Error checking absence:" << query.lastError().text();
    }

    // Afficher un QMessageBox en fonction de si des e-mails ont été envoyés ou non
    QString message = emailsSent ? "Emails were sent for absence greater than 3 days."
                                  : "No emails were sent for absence greater than 3 days.";
    QMessageBox::information(this, "Email Status", message);
}


QString MainWindow::getEmailById(int entrepreneurID)
{
    QString entrepreneurEmail;
    QSqlQuery query;
    query.prepare("SELECT EMAIL FROM ENTREPRENEURS WHERE CIN = :cin");
    query.bindValue(":cin", entrepreneurID);

    if (query.exec() && query.next()) {
        entrepreneurEmail = query.value("EMAIL").toString();
    } else {
        qDebug() << "Error: Failed to retrieve entrepreneur's email";
    }
    return entrepreneurEmail;
}



void MainWindow::emailStatus(const QString &status)
{
    qDebug() << "Email Status:" << status;
}


void MainWindow::on_mailing_clicked()
{
    checkAbsence();

}

void MainWindow::on_star_clicked()
{
    // Call Python script to scrape the website and retrieve the most recent formation
    QProcess *process = new QProcess(this);
    QString pythonScript = "C:/Users/jasse/Desktop/final/Dream-Beaver/check.py";
    process->start("python", QStringList() << pythonScript);
    process->waitForFinished();

    // Read the output of the Python script
    QByteArray output = process->readAllStandardOutput();
    QString outputStr = QString::fromUtf8(output);

    // Display the information in a QMessageBox
    QMessageBox::information(this, "Recent Formation", outputStr);
}


void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network Error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QString html = reply->readAll();
    reply->deleteLater();

    QString formationName;
    int nameStart = html.indexOf("<div class=\"produit-item__title\">");
    if (nameStart != -1) {
        nameStart = html.indexOf(">", nameStart) + 1;
        int nameEnd = html.indexOf("</div>", nameStart);
        if (nameEnd != -1) {
            formationName = html.mid(nameStart, nameEnd - nameStart).trimmed();
        }
    }

    QString startDate;
    int dateStart = html.indexOf("<div class=\"produit-item__details__items\">");
    if (dateStart != -1) {
        int spanStart = html.indexOf("<span>", dateStart);
        if (spanStart != -1) {
            spanStart = html.indexOf(">", spanStart) + 1;
            int spanEnd = html.indexOf("</span>", spanStart);
            if (spanEnd != -1) {
                startDate = html.mid(spanStart, spanEnd - spanStart).trimmed();
            }
        }
    }

    QString message = "Most Recently Added Formation:\n\n";
    message += "Formation Name: " + formationName + "\n";
    message += "Start Date: " + startDate + "\n";

    QMessageBox::information(this, "Recent Formation", message);
}

void MainWindow::checkAbsences()
{
    QDate currentDate = QDate::currentDate();
    qDebug() << "Current Date:" << currentDate.toString("yyyy-MM-dd");

    QSqlQuery query;
    query.prepare("SELECT ef.ID_ENTR, ef.ID_FORM, ef.PRESENCE, f.DF "
                  "FROM ENTREPRENEURS_FORMATIONS ef "
                  "INNER JOIN FORMATIONS f ON ef.ID_FORM = f.ID "
                  "WHERE f.DF > :currentDate");
    query.bindValue(":currentDate", currentDate);

    bool emailsSent = false;  // Flag to track if any emails were sent

    if (query.exec()) {
        bool formationsFound = false;  // Flag to track if any formations are found
        while (query.next()) {
            formationsFound = true;  // Set flag to true if any rows are found
            int entrepreneurID = query.value("ID_ENTR").toInt();
            int presence = query.value("PRESENCE").toInt();
            QDate formationDate = query.value("DF").toDate();
            int absence = currentDate.daysTo(formationDate) - presence;

            if (absence > 3) {
                mailer emailSender; // Create an instance of the mailer class
                QString entrepreneurEmail = getEmailById(entrepreneurID); // Function to get entrepreneur's email
                QString subject = "Absence Notification"; // Email subject
                QString body = "Dear Entrepreneur,\n\n"
                               "This is to inform you that you have been absent from multiple formations. "
                               "Please ensure attendance in upcoming formations.\n\n"
                               "Best regards,\n"
                               "Your Organization"; // Email body

                int result = emailSender.sendEmail(entrepreneurEmail, subject, body);
                if (result == 0) {
                    qDebug() << "Sent email to Entrepreneur with ID:" << entrepreneurID;
                    emailsSent = true;  // Set flag to true if email was sent
                } else {
                    qDebug() << "Error sending email to Entrepreneur with ID:" << entrepreneurID;
                }
            }
        }

        if (!formationsFound) {
            qDebug() << "No formations found with DF > currentDate";
        }
    } else {
        qDebug() << "Error checking absence:" << query.lastError().text();
    }

    // Show QMessageBox based on whether emails were sent or not
    QString message = emailsSent ? "Emails were sent for absence greater than 3 days."
                                  : "No emails were sent for absence greater than 3 days.";
    QMessageBox::information(this, "Email Status", message);
}
void MainWindow::RFID(int b)
{
    if (b == 1)
    {
        ui->tabs->setCurrentIndex(3);
        ui->formations->setCurrentIndex(3);
       return;
    }
    else
    {
        ui->ed->setText("xxxxxxxxxx");
        ui->itd->setText("xxxxxxxxxx");
        ui->ftype->setText("xxxxxxxxxx");
        ui->eid->setText("xxxxxxxxxx");
        ui->denied->show();
        ui->granted->hide();
        ui->yebki->show();
        ui->beaverfaehan->hide();
        ui->tabs->setCurrentIndex(5);
    }
}

void MainWindow::checkRFIDCard()
{
    int b=0;
    static QString accumulatedData;
    QByteArray newData = ard.read_from_arduino();
    QString cleanedData = QString::fromUtf8(newData).remove(QRegExp("[\\n\\r\\t]"));
    accumulatedData += cleanedData;
    if (accumulatedData.length() == 8) {
        QString IDCARD = accumulatedData.trimmed();
        qDebug() << "IDCARD:" << IDCARD;

        // Prepare and execute the query
        QSqlQuery query;
        query.prepare("SELECT e.NOM,e.cin, f.INSTRUCTEUR,f.type,ef.presence "
                      "FROM ENTREPRENEURS_FORMATIONS ef "
                      "JOIN ENTREPRENEURS e ON ef.ID_ENTR = e.CIN "
                      "JOIN FORMATIONS f ON ef.ID_FORM = f.ID "
                      "WHERE ef.IDCARD = :IDCARD");
        query.bindValue(":IDCARD", IDCARD);

        if (!query.exec()) {
            qDebug() << "Query execution failed:" << query.lastError().text();
            return;
        }

        if (query.next()) {
             entrepreneurName = query.value(0).toString();
             instructorName = query.value(2).toString();
             Identrepreneur = query.value(1).toString();
             type = query.value(3).toString();
             presence = query.value(4).toInt();
            RFID(1);
        } else {
            RFID(b);
            QByteArray noMatchMessage = "NO_MATCH";
            ard.write_to_arduino(noMatchMessage);

        }
        accumulatedData.clear();
    }
}
void MainWindow::on_yes_clicked()
{

    QString arduinoMessage = "MATCH: \n NOM:" + entrepreneurName + "\n Instructeur:" + instructorName;
    QByteArray messageBytes = arduinoMessage.toUtf8();

    ui->ed->setText(entrepreneurName);
    ui->itd->setText(instructorName);
    ui->ftype->setText(type);
    ui->eid->setText(Identrepreneur);
    ui->denied->hide();
    ui->granted->show();
    ui->yebki->hide();
    ui->beaverfaehan->show();
    ui->ed->setReadOnly(true);
    ui->itd->setReadOnly(true);
    ui->ftype->setReadOnly(true);
    ui->eid->setReadOnly(true);
    ui->tabs->setCurrentIndex(3);
    ui->formations->setCurrentIndex(4);
    ard.write_to_arduino(messageBytes);
    presence++;
    int cin = Identrepreneur.toInt();
    QSqlQuery q;
    q.prepare("UPDATE ENTREPRENEURS_FORMATIONS SET  PRESENCE = :v1 WHERE ID_ENTR = :cin");
    q.bindValue(":cin", cin);
    q.bindValue(":v1", presence);
    if (!q.exec()) {
        qDebug() << "Update failed:" << q.lastError().text();
        return;
    }else
    {
        qDebug() << "Update nejhet:" << q.lastError().text();
    }

}

void MainWindow::on_no_clicked()
{
    QString arduinoMessage ="Blacklisted";
    QByteArray messageBytes = arduinoMessage.toUtf8();
    ard.write_to_arduino(messageBytes);
    ui->ed->setText("xxxxxxxxxx");
    ui->itd->setText("xxxxxxxxxx");
    ui->ftype->setText("xxxxxxxxxx");
    ui->eid->setText("xxxxxxxxxx");
    ui->ed->setReadOnly(true);
    ui->itd->setReadOnly(true);
    ui->ftype->setReadOnly(true);
    ui->eid->setReadOnly(true);
    ui->denied->show();
    ui->granted->hide();
    ui->yebki->show();
    ui->beaverfaehan->hide();
    ui->tabs->setCurrentIndex(3);
    ui->formations->setCurrentIndex(4);

}

void MainWindow::on_search_button_f_2_clicked() {
    QString str = ui->search_formation_2->text();
    formationData = retrieveFormationDataFromDatabase(str);
    populateFormationWidgets(formationData);
}

void MainWindow::on_search_formation_2_textChanged() {
    on_search_button_f_2_clicked(); // Trigger search when text changes
}

void MainWindow::populateFormationWidgets(const QVector<FormationData> &searchResults) {
    clearFormationWidgets();

    // Clear existing layout from widget_16
    QLayout *existingLayout = ui->widget_16->layout();
    if (existingLayout) {
        QLayoutItem *child;
        while ((child = existingLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        delete existingLayout;
    }

    // Set up new layout for widget_16
    QGridLayout *widget15Layout = new QGridLayout(ui->widget_16);
    ui->widget_16->setLayout(widget15Layout);

    int row = 0;
    int column = 0;
    for (const FormationData &data : searchResults) {
        addFormationWidget(data, widget15Layout, row, column);
        column++;
        if (column == 4) {
            column = 0;
            row++;
        }
    }
}



void MainWindow::refreshFormationWidgets() {
    formationData = retrieveFormationDataFromDatabase("");
    populateFormationWidgets(formationData);
}

void MainWindow::sortFormationWidgetsByDate() {
    static Qt::SortOrder sortOrder = Qt::AscendingOrder; // Static variable to store the current sorting order

    std::sort(formationData.begin(), formationData.end(), [sortOrder](const FormationData &a, const FormationData &b) {
        return (sortOrder == Qt::AscendingOrder) ? a.dateDebut < b.dateDebut : a.dateDebut > b.dateDebut;
    });

    qDebug() << "Sorted Formation Data By Date:";
    for (const auto &data : formationData) {
        qDebug() << "ID:" << data.id << "Type:" << data.type << "Instructeur:" << data.instructeur;
    }

    populateFormationWidgets(formationData);

    // Toggle the sorting order for the next call
    sortOrder = (sortOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
}


void MainWindow::clearFormationWidgets() {
    for (FormationWidget *widget : formationWidgets) {
        widget->deleteLater();
    }
    formationWidgets.clear();
}

void MainWindow::addFormationWidget(const FormationData &data, QGridLayout *layout, int row, int column) {
    QWidget *container = new QWidget;
    container->setStyleSheet("QWidget { background-color: white; border: 2px solid blue; border-radius: 5px; padding-left: 5px; }");

    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(0, 0, 0, 0);
    containerLayout->setSpacing(0);

    FormationWidget *widget = new FormationWidget(container);
    // Set formation data using the FormationData object directly
    widget->setFormationData(data);



    containerLayout->addWidget(widget);
    layout->addWidget(container, row, column);
    connect(widget, &FormationWidget::mousePressed, this, &MainWindow::handleFormationClicked);

    container->setCursor(Qt::PointingHandCursor);

    container->setStyleSheet("QWidget:hover { background-color: lightgray; border: 2px solid blue; border-radius: 5px; padding-left: 5px; }");
}





FormationData MainWindow::extractFormationData(QStandardItemModel *model, int index) {
    FormationData data;
    // Extract formation data from the model
    data.type = model->index(index, 0).data(Qt::DisplayRole).toString();
    data.instructeur = model->index(index, 1).data(Qt::DisplayRole).toString();
    data.dateDebut = model->index(index, 2).data(Qt::DisplayRole).toDate();
    data.dateFin = model->index(index, 3).data(Qt::DisplayRole).toDate();
    data.description = model->index(index, 4).data(Qt::DisplayRole).toString();
    data.nbParticipants = model->index(index, 5).data(Qt::DisplayRole).toInt();
    data.imageData = model->index(index, 6).data(Qt::DisplayRole).toByteArray(); // Extract image data
    // Extract other FormationData fields similarly
    return data;
}

void MainWindow::handleFormationClicked() {
    FormationWidget *senderWidget = qobject_cast<FormationWidget *>(sender());
    if (senderWidget) {
        FormationData data = senderWidget->getFormationData();
        qDebug() << "Clicked Formation ID:" << data.id; // Debug statement to check the ID
        qDebug() << "Clicked Formation Type:" << data.type;
        qDebug() << "Clicked Formation Instructeur:" << data.instructeur;
        qDebug() << "Clicked Formation Date Début:" << data.dateDebut;
        qDebug() << "Clicked Formation Date Fin:" << data.dateFin;
        qDebug() << "Clicked Formation Description:" << data.description;
        qDebug() << "Clicked Formation Nombre de Participants:" << data.nbParticipants;
        qDebug() << "Clicked Formation Image Size:" << data.imageData.size(); // Debug statement for image data size

        // Set the formation data to the modification form in the stacked widget
        ui->ID_formation_2->setText(QString::number(data.id));
        ui->type_formation_2->setCurrentText(data.type);
        ui->instructeur_2->setText(data.instructeur);
        ui->dateDebut_3->setDate(data.dateDebut);
        ui->dateFin_3->setDate(data.dateFin);
        ui->description_3->setText(data.description);
        ui->nbParticipants_2->setText(QString::number(data.nbParticipants));

        // Switch to the modification form in the stacked widget
        ui->formations->setCurrentIndex(2);
    }
}


QVector<FormationData> MainWindow::retrieveFormationDataFromDatabase(const QString &str) {
    QVector<FormationData> formations;

    // Assuming there's a database connection established earlier

    // Prepare the query
    QString queryString = "SELECT ID, TYPE, INSTRUCTEUR, DD, DF, DESCRIPTION, NB_PARTICIPANTS, IMAGE FROM FORMATIONS";
    if (!str.isEmpty()) {
        queryString += " WHERE TYPE LIKE '%" + str + "%' OR INSTRUCTEUR LIKE '%" + str + "%' OR DESCRIPTION LIKE '%" + str + "%'";
        // Add additional conditions for other columns if needed
    }

    // Retrieve formation data from the database
    QSqlQuery query(queryString);
    while (query.next()) {
        FormationData data;
        data.id = query.value(0).toInt();
        data.type = query.value(1).toString();
        data.instructeur = query.value(2).toString();
        data.dateDebut = query.value(3).toDate();
        data.dateFin = query.value(4).toDate();
        data.description = query.value(5).toString();
        data.nbParticipants = query.value(6).toInt();
        data.imageData = query.value(7).toByteArray(); // Retrieve image data
        formations.append(data);
    }

    return formations;
}
void MainWindow::sortFormationWidgetsByParticipants() {
    static Qt::SortOrder sortOrder = Qt::AscendingOrder; // Static variable to store the current sorting order

    std::sort(formationData.begin(), formationData.end(), [sortOrder](const FormationData &a, const FormationData &b) {
        return (sortOrder == Qt::AscendingOrder) ? a.nbParticipants < b.nbParticipants : a.nbParticipants > b.nbParticipants;
    });

    qDebug() << "Sorted Formation Data By Number of Participants:";
    for (const auto &data : formationData) {
        qDebug() << "ID:" << data.id << "Type:" << data.type << "Participants:" << data.nbParticipants;
    }

    populateFormationWidgets(formationData);

    // Toggle the sorting order for the next call
    sortOrder = (sortOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
}

void MainWindow::on_tri_typefor_2_clicked()
{
    sortFormationWidgetsByDate();
}

void MainWindow::on_tri_nbrfor_2_clicked()
{
    sortFormationWidgetsByParticipants();
}
void MainWindow::on_tri_formation_2_clicked()
{
    if(!i) {
         ui->tri_bar_formation_2->hide() ;
         i=1 ;
    }
    else {
         ui->tri_bar_formation_2->show() ;
         i=0 ;
    }
}

void MainWindow::on_pdf_formation_2_clicked()
{
    on_pdf_formation_clicked();
}

void MainWindow::on_add_formation_2_clicked()
{
    on_add_formation_clicked();
}

void MainWindow::on_mailing_2_clicked()
{
    on_mailing_clicked();
}

void MainWindow::on_star_2_clicked()
{
    on_star_clicked();
}


void MainWindow::on_pushButton_5_clicked()
{
    // Open a file dialog to select an image
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", QDir::homePath(), "Images (*.png *.jpg *.jpeg)");

    // Check if the user selected an image
    if (!imagePath.isEmpty()) {
        // Display the selected image (optional)
        QPixmap imagePreview(imagePath);
        ui->label_image_preview->setPixmap(imagePreview.scaled(ui->label_image_preview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        // Convert the selected image to a QByteArray
        QImage image(imagePath);
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");

        // Store the image data for later use in on_add_form_clicked()
        selectedImageData = imageData;
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", QDir::homePath(), "Images (*.png *.jpg *.jpeg)");

    // Check if the user selected an image
    if (!imagePath.isEmpty()) {
        // Display the selected image (optional)
        QPixmap imagePreview(imagePath);
        ui->label_image_preview_2->setPixmap(imagePreview.scaled(ui->label_image_preview_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        // Convert the selected image to a QByteArray
        QImage image(imagePath);
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");

        // Store the image data for later use in on_add_form_clicked()
        selectedImageData = imageData;
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    on_pushButton_8_clicked();
}
