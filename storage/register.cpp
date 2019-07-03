#include "register.h"
#include "ui_register.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include <QMessageBox>
#include <QDebug>
Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
   ui->setupUi(this);
   int width = this->geometry().width();
   int height = this->geometry().height();
   this->setFixedSize(width,height); //设置窗体固定大小

   ui->userEdit->setFocus();//聚焦
   ui->userEdit->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9]+$")));
   ui->passwordEdit->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9]+$")));
   setWindowTitle(tr("注册"));
   ui->passwordEdit->setEchoMode(QLineEdit::Password);
   db3 = QSqlDatabase::addDatabase("QSQLITE", "db3");
   db3.setDatabaseName("nbut.zh");
   db3.open();

   QPixmap pi(":/images/zhuce.jpg");
   QPalette pa;
   pa.setBrush(QPalette::Background,QBrush(pi));
   setPalette(pa);

}

Register::~Register()
{
    delete ui;
}

void Register::on_okButton_clicked()
{

    QSqlQuery query(db3);
    query.exec("create table if not exists passw(user varchar primary key,pwd varchar)");
    if(ui->passwordEdit->text().isEmpty() && ui->userEdit->text().isEmpty())
   {
       QMessageBox::warning(this,tr("注册失败"),tr("用户名或密码不能为空"),QMessageBox::Ok);
       ui->userEdit->clear();
       ui->passwordEdit->clear();
       ui->userEdit->setFocus();
   }
   else{

   QString stru=ui->userEdit->text().trimmed();//编辑框中的文本赋给变量
   QString strp=ui->passwordEdit->text().trimmed();

   QString sql;
   sql="select * from passw where user='";
   sql=sql+stru;
   sql=sql+"'";
   query.exec(sql);
   query.first();
   if(query.value(0).isNull())
   {
   QString password;
   password="insert into passw values('"+stru+"','"+strp+"')";
   query.exec(password);
   QMessageBox::information(this,tr("注册"), tr("仓库管理系统管理员注册成功，请登录使用"),QMessageBox::Ok);
   QDialog::accept();
   }
   else
   {
       QMessageBox::information(this,tr("注册"), tr("该用户已被注册过"),QMessageBox::Ok);
       ui->userEdit->clear();
       ui->passwordEdit->clear();
       ui->userEdit->setFocus();
   }

   }

}

void Register::on_cancelButton_clicked()
{
    QDialog::reject();
}
