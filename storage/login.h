#ifndef LOGIN_H
#define LOGIN_H
#include <QSqlDatabase>
#include <register.h>
#include <QtWidgets>
#include "register.h"


class Login: public QDialog
{
    Q_OBJECT
public:
    explicit Login();
    ~Login();
private slots:
    void zhuce();
    void loginsystem();
private:
    Register  regist;
    QLineEdit *user;
    QLineEdit *password;
    QSqlDatabase db2;
    QPixmap *pi;
    QPalette *pa;
    QString userName;
public:
    QString getusername();//获取用户名

};

#endif // LOGIN_H
