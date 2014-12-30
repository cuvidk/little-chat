#include "login.h"
#include "ui_login.h"

Login::Login(char* ip, char* name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    name(name),
    ip(ip)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin1_clicked()
{
    QString Qname = ui->txtNickname1->text();
    std::string name = Qname.toStdString();

    if(name != "")
    {
        strcpy(this->name, name.c_str());
        this->close();
    }
    else
        QMessageBox::information(NULL, "Usefull", "Please fill in the nickname.","OK");
}


void Login::on_btnLogin2_clicked()
{
    QString Qname = ui->txtNickname2->text();
    std::string name = Qname.toStdString();

    QString Qip = ui->txtIP->text();
    std::string ip = Qip.toStdString();

    if (name != "" && ip != "")
    {
        strcpy(this->name, name.c_str());
        strcpy(this->ip, ip.c_str());
        this->close();
    }
    else
        QMessageBox::information(NULL, "Usefull", "Please fill in both fields.","OK");
}
