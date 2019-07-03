#include <QApplication>
#include "storage.h"
#include "QTextCodec"
#include <login.h>
#include <QSqlQuery>
#include <QSqlDatabase>
int main(int argc, char *argv[])
{   QApplication a(argc, argv);

    QElapsedTimer t;//计时器
    QSplashScreen splash(QPixmap(":/images/storage.png"));
    splash.setDisabled(true); //禁用用户的输入事件响应

    storage w;

    Login dlg;
    dlg.setWindowTitle("登录");
    if(dlg.exec()==QDialog::Accepted)
    {
    QString  user = dlg.getusername();
    splash.show();
    t.start();//计时器功能：开启应用显示的图片界面事件
    while(t.elapsed()<2000)
    {
        QCoreApplication::processEvents();
    }
     splash.finish(&w);
     w.setStringData(user);
    w.show();
    return a.exec();
   }
    return 0;
}
