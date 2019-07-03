#ifndef STORAGE_H
#define STORAGE_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include <QtWidgets>
#include <comboboxdelegate.h>
#include <memorandum.h>
#include "pieview.h"
class QTableWidget;
class QGroupBox;
class QLineEdit;
class QSpinBox;
class QTableView;
class QAction;
class QMenu;
class QToolBar;
class QDateEdit;
QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class QAbstractItemView;
class QItemSelectionModel;
QT_END_NAMESPACE

//class QRadioButton;


class storage : public QMainWindow
{
    Q_OBJECT
public:
    storage(QWidget *parent = 0);
    ~storage();
     void createMenus();
     void createActions();
     void createToolbar();
     void creatdockwidget();
     void setStringData(QString user);

private:
     QString user;
private:
    //QTableWidget *table;
    QDockWidget *dock;
    Memorandum *memorandum;
    ComboBoxDelegate *date;
    QTableView *table;
    QTableView *docktable;
    QSqlTableModel *dockmodel;
    //QTableView *saletable;
    QSqlTableModel *model;
    QGroupBox *instorage;
    QGroupBox *outstorage;
    QGroupBox *adddata;
    QLabel *msgLabel;
    QLineEdit *inname;
    QLineEdit *inremark;
    QLineEdit *inprice;
    QSpinBox *incount;
    QLineEdit *inid;
    QLineEdit *outid;
    QSpinBox *outcount;
    QLineEdit *outname;
    //QLineEdit *outprice;
    QLineEdit *outremark;
    QLineEdit *passw;
    QLineEdit *oldpassw;
    QLineEdit *surepassw;
    QLineEdit *findedit;
    QGroupBox *pswstorage;
    QGroupBox *findstorage;
    QGroupBox *salestorage;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *systemenu;
    QMenu *managemenu;
    QMenu *daorumenu;
    QMenu *helpMenu;
    QToolBar *toolbar1;
    QToolBar *toolbar2;
    QToolBar *toolbar3;
    QAction *aboutAct;
    QAction *watchtable;
    QAction *daochu;
    QAction *Find;
    QAction *chuku;
    QAction *bwl;
    QAction *saletable;
    QAction *computer;
    QAction *toolmanage;
    QAction *exitsystem;
    QAction *supplier;
    QAction *customer;
    QAction *locksyatem;
    QAction *ruku;
    QAction *ableEdit;
    QAction *enableEdit;
    QAction *sysset;
    //QRadioButton *radio;
    QAction *action_show;
    QAction *action_quit;
    QAction *action_set;
    QAction *action_updata;
    QPixmap *pi;
    QPalette *pa;
    QSqlDatabase db;//数据库
    QSqlDatabase db2;//登录密码数据库定义
    QPlainTextEdit *textEdit;//备忘录
    QGroupBox *systemset;//系统设置
    QListWidget *listwidget;
    QStackedWidget *stack;
    QListWidgetItem *item;
    QAbstractItemModel *salemodel;
    PieView *pieChart;
private slots:
   //左侧菜单栏左键注册
    void menu1_1click();
    void menu1_2click();
    void menu1_3click();
    void menu3_2click();
    void menu3_1click();
    void menu3_5click();
    void menu3_0click();
    void menu3_3click();
    void menu3_4click();
    void menu3_6click();
    void menu4_1click();
    void menu1_4click();
    void menu2_0click();
    void menu4_2click();
    void menu2_3click();
    void in();//入库
    void out();//出库
    void updatapsw();//更新密码
    void Findstorage();//查询操作
    //菜单栏事件
    void about();
    void daochuE();
    void enableedit();
    void ableedit();
    void tooltri();
    void supplierabout();//供货商接口
    void customerabout();//顾客资料接口
    void addData();//添加客户供货商资料
    void deleteData();
    void commitData();

private slots:
    void opensaleFile();
    void savesaleFile();
    void statusUpDate();

    void iconIsActived(QSystemTrayIcon::ActivationReason reason);
   // void findNext(const QString &str, Qt::CaseSensitivity cs);
   // void findPrevious(const QString &str, Qt::CaseSensitivity cs);
private:
    void readSettings();
    void writeSettings();



};

#endif // STORAGE_H
