#include "login.h"
#include "ui_login.h"

Login::Login(char* name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    name(name)
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

