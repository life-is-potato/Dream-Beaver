#include "login.h"
#include "ui_login.h"
#include "QMessageBox"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    connect(ui->loginbutton, &QPushButton::clicked, this, &login::on_loginbutton_clicked);
}

login::~login()
{
    delete ui;
}
void login::on_loginbutton_clicked()
{

    QString username = ui->username->text();
    QString password = ui->password->text();
    if (username=="walhazi" && password=="walhazi") {
        emit loginSuccess();
        accept();
    } else {
        QMessageBox::warning(this, "Login Failed", "ghalet please enter username and password");
    }
}
void login::on_close_clicked()
{
    exit(0);
}
