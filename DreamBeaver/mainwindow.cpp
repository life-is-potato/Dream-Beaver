#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tableView, &QAbstractItemView::doubleClicked, this, &MainWindow::handleItemDoubleClicked);
    connect(ui->tableView, &QAbstractItemView::clicked, this, &MainWindow::handleItemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
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
        ui->birthday->clearMask();
        return;
    }
    if (!phoneRegex.match(phoneText).hasMatch()) {
        ui->phone_2->setText("Invalid phone number");
        ui->fname->clear();
        ui->lname->clear();
        ui->birthday->clearMask();
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

