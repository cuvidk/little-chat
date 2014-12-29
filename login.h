#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <qmessagebox.h>
#include <string>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(char* name, QWidget *parent = 0);
    ~Login();

private slots:
    void on_btnLogin1_clicked();

private:
    Ui::Login *ui;
    char* name;
};

#endif // LOGIN_H
