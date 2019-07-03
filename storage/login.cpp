#include "login.h"
#include "QtWidgets"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>

Login::Login()
{
    setFixedSize(682,478);
    QPixmap pi(":/images/background.png");
    QSize size(this->width(),this->height());
    QPixmap pc(pi.scaled(size));
    QPalette pa;
    pa.setBrush(QPalette::Background,QBrush(pc));
    setPalette(pa);
//    QPalette pa;
//    pa.setColor(QPalette::Background,Qt::blue);//设置背景颜色
    QWidget *top=new QWidget();
    //top->setFixedSize(750,80);
    top->setAutoFillBackground(true);
    //top->setPalette(pa);
    //-------------中间区域------------
    QWidget *mid=new QWidget();
    //mid->setFixedSize(750,320);
    mid->setAutoFillBackground(true);
   // mid->setStyleSheet("background:lightblue");
    user=new QLineEdit;
    password=new QLineEdit;
    user->setFixedWidth(100);
    password->setFixedWidth(100);
    QLabel *title=new QLabel("<i><font size=\"5\"><font color=\"#0000dd\"><strong>欢 迎 登 陆</FONT></strong></i>");
    title->setAlignment(Qt::AlignCenter);
    QLabel *titlelogo=new QLabel;
    titlelogo->setFixedSize(37,37);
    QImage *ppm = new QImage(":/images/logo_2.png");
 // title->setScaledContents(true);标签+入图片自适应大小
    titlelogo->setScaledContents(true);
    titlelogo->setPixmap(QPixmap::fromImage(*ppm));
    QPushButton *regist=new QPushButton("注册");
    regist->setFixedWidth(80);
    QPushButton *login=new QPushButton("登录");
    login->setFixedWidth(80);
    login->setFocus();
    login->setShortcut( QKeySequence::InsertParagraphSeparator );
    QHBoxLayout *midlayout3=new QHBoxLayout;
    midlayout3->addStretch();
    midlayout3->addWidget(titlelogo);
    midlayout3->addWidget(title);
     midlayout3->addStretch();
    QHBoxLayout *midlayout=new QHBoxLayout;
    midlayout->addStretch();
    midlayout->addWidget(new QLabel(tr("用户名:")));
    midlayout->addWidget(user);
    midlayout->addStretch();
    QHBoxLayout *midlayout2=new QHBoxLayout;
    midlayout2->addStretch();
    midlayout2->addWidget(new QLabel(tr("密　码:")));
    midlayout2->addWidget(password);
    midlayout2->addStretch();
    QHBoxLayout *midbut=new QHBoxLayout;
    midbut->addStretch();
    midbut->addWidget(regist);
    midbut->addWidget(login);
    midbut->addStretch();
    QVBoxLayout *mainlayout=new QVBoxLayout;
    mainlayout->addStretch();
    mainlayout->addLayout(midlayout3);
    mainlayout->addLayout(midlayout);
    mainlayout->addLayout(midlayout2);
    mainlayout->addLayout(midbut);
    mainlayout->addStretch();
    mid->setLayout(mainlayout);
    //------------底下区域-------------
    QWidget *under=new QWidget();
    //under->setFixedSize(750,50);
    under->setAutoFillBackground(true);
    //under->setPalette(pa);
//    QLabel *underlabel=new QLabel(tr("仓库管理系统 版权所有 违者必究 \n guojianyong.ys168.com"),under);
//    underlabel->setFixedSize(750,50);
//    underlabel->setAlignment(Qt::AlignCenter);
    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(top);
    layout->addWidget(mid);
    layout->addWidget(under);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);
    connect(regist,SIGNAL(clicked()),this,SLOT(zhuce()));
    connect(login,SIGNAL(clicked()),this,SLOT(loginsystem()));

    user->setFocus();//聚焦
    password->setEchoMode(QLineEdit::Password);//密码不可见
    db2 = QSqlDatabase::addDatabase("QSQLITE", "db2");
    db2.setDatabaseName("nbut.zh");
    db2.open();
    //query.exec("create table passw(pwd varchar primary key)");
    //query.exec("insert into passw values('123')");


}
void Login::loginsystem()
{


    if(user->text().isEmpty()&&password->text().isEmpty())
   {
       QMessageBox::information(this,tr("欢迎使用仓库管理系统"),tr("输入错误"),QMessageBox::Ok);
       user->clear();
       password->clear();
       user->setFocus();
   }
   else
   {
       QSqlQuery query(db2);
       QString getUser=user->text();
       QString sql;
       sql="select * from passw where user='";
       sql=sql+getUser;
       sql=sql+"'";
       //query.exec("select pwd from passw");
       query.exec(sql);
       query.first();
       qDebug()<<"账号："<<query.value(0).toString();
       qDebug()<<"密码："<<query.value(1).toString();
       if(query.value(1).toString()==password->text())
       {
           QDialog::accept();
        }
       else
       {
        QMessageBox::warning(this,tr("密码错误"), tr("请输入正确密码后再登录"),QMessageBox::Ok);
        password->clear();//清楚密码里的原有内容
        password->setFocus();
       }
        userName=getUser;
   }

}

QString Login::getusername()
{
    return userName;
}

Login::~Login()
{
  db2.close();
}
void Login::zhuce()
{
    if(regist.exec()==QDialog::Accepted)
    {


    }
}

