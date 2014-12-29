#include "chat.h"
#include "ui_chat.h"

Chat::Chat(int* sd, struct package* mainInfo, char* name, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chat),
    sd(sd),
    mainInfo(mainInfo),
    name(name)
{
    ui->setupUi(this);
}

void Chat::setMessage(const std::string& msg)
{
    ui->txtMessages->append(QString::fromStdString(msg));
}

void Chat::clearOnline()
{
    ui->listOnline->clear();
}

void Chat::populateOnline(char names[100][30], int number)
{
    for(int i = 0; i < number; i++)
    {
        std::string name(names[i]);
        ui->listOnline->addItem(QString::fromStdString(name));
    }
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_btnSend_clicked()
{
    strcpy(mainInfo->name, name);
    QString Qmessage = ui->textEntry->toPlainText();
    std::string message = Qmessage.toStdString();
    strcpy(mainInfo->message, message.c_str());
    ui->textEntry->clear();

    if (send(*sd, mainInfo, sizeof(struct package), 0) < 0)
        error("Error sending the message");
}
