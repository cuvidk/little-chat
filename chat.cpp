#include "chat.h"
#include "ui_chat.h"

#include <QShortcut>
#include <QKeyEvent>
#include <QScrollBar>

Chat::Chat(int* sd, struct package* mainInfo, char* name, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chat),
    sd(sd),
    mainInfo(mainInfo),
    name(name)
{
    ui->setupUi(this);
    ui->textEntry->installEventFilter(this);
    QScrollBar* scrollbar = ui->txtMessages->verticalScrollBar();
    QObject::connect(scrollbar, SIGNAL(rangeChanged(int,int)), this, SLOT(moveScrollBarToBottom(int, int)));
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

    std::string Sname(name);
    std::string myMessage =  "Me(" + Sname + "): " + message;
    this->setMessage(myMessage);

    if (send(*sd, mainInfo, sizeof(struct package), 0) < 0)
        error("Error sending the message");
}

bool Chat::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->textEntry && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return)
        {
            ui->btnSend->click();
            return true;
        }
        else
        {
            return QMainWindow::eventFilter(object, event);
        }
    }
    else
    {
        return QMainWindow::eventFilter(object, event);
    }
}

void Chat::moveScrollBarToBottom(int min, int max)
{
    Q_UNUSED(min);
    ui->txtMessages->verticalScrollBar()->setValue(max);
}
