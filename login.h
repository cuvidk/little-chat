#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <qmessagebox.h>
#include <string>
#include <iostream>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(char* ip, char* name, QWidget *parent = 0);
    ~Login();

private slots:
    void on_btnLogin1_clicked();
    void on_btnLogin2_clicked();

private:
    Ui::Login *ui;
    char* name;
    char* ip;
};

#endif // LOGIN_H
