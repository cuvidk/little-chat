#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include "usefull.h"
using namespace Usefull;

namespace Ui {
class Chat;
}

class Chat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chat(int* sd, struct package* mainInfo, char* name, QWidget *parent = 0);
    void setMessage(const std::string& msg);
    void clearOnline();
    void populateOnline(char names[100][30], int number);
    ~Chat();

private slots:
    void on_btnSend_clicked();

private:
    Ui::Chat *ui;
    int* sd;
    struct package* mainInfo;
    char* name;
};

#endif // CHAT_H
