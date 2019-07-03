#include "storage.h"
#include "memorandum.h"
#include "calculator.h"
#include "pieview.h"
#include "QDesktopWidget"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QMessageBox"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QFont>
storage::storage(QWidget *parent)
    : QMainWindow(parent)
{

    //---------------------初始化--------------------------------------------------
    setWindowTitle(tr("仓库管理系统"));
    QDesktopWidget* dw = new QDesktopWidget();
    int window_width=840;
    int window_height=480;
    setGeometry((dw->screenGeometry().width()-window_width)/2,(dw->screenGeometry().height()-window_height)/2,window_width,window_height);
    resize(1040,580);
    createActions();
    createMenus();
    createToolbar();
    creatdockwidget();
   addDockWidget(Qt::RightDockWidgetArea,dock);
    QPalette pb;
     pb.setColor(QPalette::WindowText,Qt::blue);
    //----------------------状态栏初始化------------
    QTimer *timer = new QTimer(this);//新建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(statusUpDate()));//关联定时器计满信号和相应的槽函数
    timer->start(1000);
    msgLabel=new QLabel();
    msgLabel->setPalette(pb);
    statusBar()->addPermanentWidget(msgLabel);
    statusBar()->insertWidget(0,new QLabel(tr("欢迎使用仓库管理系统")));
   // statusBar()->insertWidget(2,msgLabel);
    //----------------------设置托盘----------------------
    QSystemTrayIcon *system_tray = new QSystemTrayIcon(this);
    //放在托盘提示信息
    system_tray ->setToolTip(QString("仓库管理系统"));
    system_tray ->setIcon(QIcon(":/images/piga.png"));
    //创建托盘项
    QMenu *tray_menu = new QMenu;//托盘菜单
    action_show = new QAction(this);
    action_show->setText(tr("打开主面板"));
    action_show->setIcon(QIcon(":/images/open.png"));
    action_quit = new QAction(this);
    action_quit->setText(tr("关闭"));
    action_quit->setIcon(QIcon(":/images/close.png"));
    action_set=new QAction(this);
    action_set->setText(tr("设置"));
    action_set->setIcon(QIcon(":/images/setting.png"));
    action_updata=new QAction(this);
    action_updata->setText(tr("更新"));
    action_updata->setIcon(QIcon(":/images/updata.png"));

    tray_menu->addAction(action_show);
    tray_menu->addAction(action_set);
    tray_menu->addAction(action_updata);
    tray_menu->addSeparator();
    tray_menu->addAction(action_quit);
    system_tray->setContextMenu(tray_menu);
    //点击托盘执行的事件
    connect(system_tray , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    connect(action_quit,SIGNAL(triggered()),this,SLOT(close()));
    connect(action_show,SIGNAL(triggered()),this,SLOT(showNormal()));
    connect(action_set,SIGNAL(triggered()),this,SLOT(menu4_2click()));
    //显示托盘
    system_tray->show();
    system_tray->showMessage(QString("仓库管理系统"), QString("点击托盘进行管理"));
  //-------------------------------开始制作左边菜单----------------------------------
    QGroupBox *menu1=new QGroupBox();//第一个菜单
    menu1->setMaximumWidth(100);
    QToolButton *menu1_1=new QToolButton();
    menu1_1->setText(tr("仓库管理"));
    menu1_1->setIcon(QPixmap(":/images/cangku_2.png"));
    menu1_1->setIconSize(QPixmap(":/images/cangku_2.png").size());
    menu1_1->setAutoRaise(true);
    menu1_1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu1_2=new QToolButton();
    menu1_2->setText(tr("仓库入库"));
    menu1_2->setIcon(QPixmap(":/images/ruku.png"));
    menu1_2->setIconSize(QPixmap(":/images/hh.png").size());
    menu1_2->setAutoRaise(true);
    menu1_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu1_3=new QToolButton();
    menu1_3->setText(tr("仓库出库"));
    menu1_3->setIcon(QPixmap(":/images/chuku.png"));
    menu1_3->setIconSize(QPixmap(":/images/jj.png").size());
    menu1_3->setAutoRaise(true);
    menu1_3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu1_4=new QToolButton();
    menu1_4->setText(tr("备忘录"));
    menu1_4->setIcon(QPixmap(":/images/bwl.png"));
    menu1_4->setIconSize(QPixmap(":/images/bwl.png").size());
    menu1_4->setAutoRaise(true);
    menu1_4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QVBoxLayout *menu1_layout=new QVBoxLayout(menu1);
    menu1_layout->setMargin(10);
    menu1_layout->setAlignment(Qt::AlignHCenter);
    menu1_layout->addWidget(menu1_1);
    menu1_layout->addWidget(menu1_2);
    menu1_layout->addWidget(menu1_3);
    menu1_layout->addWidget(menu1_4);
    menu1_layout->addStretch();
    //第二个菜单栏
    QGroupBox *menu2=new QGroupBox();
    menu2->setMaximumWidth(100);
    QToolButton *menu2_0=new QToolButton();
    menu2_0->setText(tr("销售额"));
    menu2_0->setIcon(QPixmap(":/images/xiaoshoue.png"));
    menu2_0->setIconSize(QPixmap(":/images/xiaoshoue.png").size());
    menu2_0->setAutoRaise(true);
    menu2_0->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu2_1=new QToolButton();
    menu2_1->setText(tr("结果统计"));
    menu2_1->setIcon(QPixmap(":/images/yy.png"));
    menu2_1->setIconSize(QPixmap(":/images/yy.png").size());
    menu2_1->setAutoRaise(true);
    menu2_1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu2_3=new QToolButton();
    menu2_3->setText(tr("计算器"));
    menu2_3->setIcon(QPixmap(":/images/jisuanqi.png"));
    menu2_3->setIconSize(QPixmap(":/images/jisuanqi.png").size());
    menu2_3->setAutoRaise(true);
    menu2_3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu2_2=new QToolButton();
    menu2_2->setText(tr("报表打印"));
    menu2_2->setIcon(QPixmap(":/images/nn.png"));
    menu2_2->setIconSize(QPixmap(":/images/nn.png").size());
    menu2_2->setAutoRaise(true);
    menu2_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QVBoxLayout *menu2_layout=new QVBoxLayout(menu2);
    menu2_layout->setMargin(10);
    menu2_layout->addWidget(menu2_0);
    menu2_layout->addWidget(menu2_1);
    menu2_layout->addWidget(menu2_3);
    menu2_layout->addWidget(menu2_2);
    menu2_layout->setAlignment(Qt::AlignHCenter);
    menu2_layout->addStretch();
    //第三个个菜单栏
    QGroupBox *menu3=new QGroupBox();
    menu3->setMaximumWidth(100);
    QToolButton *menu3_0=new QToolButton();
    menu3_0->setText("添加信息");
    menu3_0->setIcon(QPixmap(":/images/mm.png"));
    menu3_0->setIconSize(QPixmap(":/images/mm.png").size());
    menu3_0->setStatusTip(tr("在数据表中添加商品信息"));
    menu3_0->setAutoRaise(true);
    menu3_0->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu3_1=new QToolButton();
    menu3_1->setText("查询数据");
    menu3_1->setIcon(QPixmap(":/images/aa.png"));
    menu3_1->setIconSize(QPixmap(":/images/aa.png").size());
    menu3_1->setAutoRaise(true);
    menu3_1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu3_2=new QToolButton();
    menu3_2->setText("删除信息");
    menu3_2->setIcon(QPixmap(":/images/cc.png"));
    menu3_2->setIconSize(QPixmap(":/images/cc.png").size());
    menu3_2->setAutoRaise(true);
    menu3_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu3_6=new QToolButton();
    menu3_6->setText("撤销修改");
    menu3_6->setIcon(QPixmap(":/images/qq.png"));
    menu3_6->setIconSize(QPixmap(":/images/qq.png").size());
    menu3_6->setAutoRaise(true);
    menu3_6->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu3_3=new QToolButton();
    menu3_3->setText("按编号升序");
    menu3_3->setIcon(QPixmap(":/images/ss.png"));
    menu3_3->setIconSize(QPixmap(":/images/ss.png").size());
    menu3_3->setAutoRaise(true);
    menu3_3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu3_4=new QToolButton();
    menu3_4->setText("按编号降序");
    menu3_4->setIcon(QPixmap(":/images/dd.png"));
    menu3_4->setIconSize(QPixmap(":/images/dd.png").size());
    menu3_4->setAutoRaise(true);
    menu3_4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu3_5=new QToolButton();
    menu3_5->setText("提交");
    menu3_5->setIcon(QPixmap(":/images/tt.png"));
    menu3_5->setIconSize(QPixmap(":/images/tt.png").size());
    menu3_5->setAutoRaise(true);
    menu3_5->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QVBoxLayout *menu3_layout=new QVBoxLayout(menu3);
    menu3_layout->setMargin(10);
    menu3_layout->addWidget(menu3_0);
    menu3_layout->addWidget(menu3_1);
    menu3_layout->addWidget(menu3_2);
    menu3_layout->addWidget(menu3_6);
    menu3_layout->addWidget(menu3_3);
    menu3_layout->addWidget(menu3_4);
    menu3_layout->addWidget(menu3_5);
    menu2_layout->setAlignment(Qt::AlignHCenter);
    menu2_layout->addStretch();
    //第四个菜单栏
    QGroupBox *menu4=new QGroupBox();
    menu4->setMaximumWidth(100);
    QToolButton *menu4_1=new QToolButton();
    menu4_1->setText("密码重置");
    menu4_1->setIcon(QPixmap(":/images/ee.png"));
    menu4_1->setIconSize(QPixmap(":/images/ee.png").size());
    menu4_1->setAutoRaise(true);
    menu4_1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QToolButton *menu4_2=new QToolButton();
    menu4_2->setText("系统设置");
    menu4_2->setIcon(QPixmap(":/images/sz.png"));
    menu4_2->setIconSize(QPixmap(":/images/sz.png").size());
    menu4_2->setAutoRaise(true);
    menu4_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QVBoxLayout *menu4_layout=new QVBoxLayout(menu4);
    menu4_layout->setMargin(10);
    menu4_layout->addWidget(menu4_1);
    menu4_layout->addWidget(menu4_2);
    menu4_layout->setAlignment(Qt::AlignHCenter);
    menu4_layout->addStretch();

    //----------------设置菜单栏事件-----------------------------
    QToolBox *menu=new QToolBox();
    menu->setMaximumWidth(100);
    menu->setMinimumWidth(100);
    menu->addItem(menu1,tr("仓库管理"));
    menu->addItem(menu3,tr("数据操作"));
    menu->addItem(menu2,tr("报表"));
    menu->addItem(menu4,tr("设置"));
   //menu->setFixedSize(100,500); //设置窗体固定大小
   /*---------管理仓库数据表(QTablewidget)-----暂时没用---------------
    table=new QTableWidget;
    QStringList table_head;
    table_head << "编号" << "名称" <<"数量"<<"进货日期"<< "备注";
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(table_head);
    //table->setEditTriggers(QAbstractItemView:: SelectedClicked);//设置文本不可编辑
    table->horizontalHeader()->setStretchLastSection(true);//设置充满表宽度
   // table->setFrameShape(QFrame::NoFrame);//设置无边框
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置多选
    table->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选择单行
    table->verticalHeader()->setDefaultSectionSize(25);//设置行高
    table->setColumnWidth(0,50);//设置表头第一列的宽度
    table->horizontalHeader()->resizeSection(4,200);//设置表头第二列的宽度
    table->setStyleSheet("selection-background-color:lightblue;");//设置选中背景的颜色
    table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//设置表头背景颜色(天蓝)
    table->horizontalHeader()->setStretchLastSection(true);//设置table宽度自动
    //table->setHidden(true);//行名隐藏
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    */
    //------------------------建立数据库表QTableview-----------------------
     table=new QTableView(this);
     table->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置多选

     table->setSelectionBehavior(QAbstractItemView::SelectRows);//设置单行
     table->horizontalHeader()->setStretchLastSection(true);//设置充满表宽度
     table->setStyleSheet("background:transparent");
     table->verticalHeader()->setDefaultSectionSize(25);//设置行高
     table->setColumnWidth(0,50);//设置表头第一列的宽度
     table->horizontalHeader()->resizeSection(4,200);//设置表头第二列的宽度
     table->setStyleSheet("selection-background-color:lightblue;");//设置选中背景的颜色
     table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//设置表头背景颜色(天蓝)
     date=new ComboBoxDelegate();
     table->setItemDelegateForColumn(2,date);
    //---------------------------建立数据库---------------------------------------------shujuku
    db =QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("nbut.zh"); // 数据库名与路径, 此时是放在同目录下
    bool ok=db.open(); // 连接数据库, 然后就可以使用了
    if(ok) qDebug()<<"connect ok!";//测试数据库是否已经成功打开*/
    QSqlQuery query;
    query.exec("create table if not exists goods (id integer primary key,name varchar(20),date varchar(20),count int,price varchar(20),remark varchar(255))");
    query.exec("create table if not exists customer (id integer primary key,name varchar(20),date varchar(20),remark varchar(255))");
    query.exec("create table if not exists supplier (id integer primary key,name varchar(20),date varchar(20),remark varchar(255))");
    model = new QSqlTableModel(this);
    model->setTable("goods");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行
    // model->removeColumn(1); //不显示name属性列,如果这时添加记录，则该属性的值添加不上
    table->setModel(model);
    model->setHeaderData(0,Qt::Horizontal,tr("编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("时间"));
    model->setHeaderData(3,Qt::Horizontal,tr("数量"));
    model->setHeaderData(4,Qt::Horizontal,tr("价格"));
    model->setHeaderData(5,Qt::Horizontal,tr("供货商"));
    //model->clear();
    //table->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    dockmodel = new QSqlTableModel;
    dockmodel->setTable("supplier");
    dockmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    dockmodel->select(); //选取整个表的所有行
    // model->removeColumn(1); //不显示name属性列,如果这时添加记录，则该属性的值添加不上
    docktable->setModel(dockmodel);
    //--------------------------添加客户，供货商资料界面---------
    //adddata=new QGroupBox(tr("添加数据信息"));

    //--------------------------入库-------------------
    instorage=new QGroupBox(tr("入库"));
    QFormLayout *in_storage=new QFormLayout(instorage);
    incount=new QSpinBox();
    incount->setMaximum(10000);
    incount->setMinimumWidth(100);
    incount->setMaximumWidth(100);
    QPushButton *in_submit=new QPushButton(tr("入库"));
    in_submit->setMaximumWidth(50);
    inname=new QLineEdit();
    inremark=new QLineEdit();
    inprice=new QLineEdit();
    inid=new QLineEdit();
    inname->setFixedWidth(200);
    inremark->setFixedWidth(200);
    inid->setFixedWidth(200);
    inprice->setFixedWidth(200);
    in_storage->addRow(new QLabel(tr("商品编号:")),inid);
    in_storage->addRow(new QLabel(tr("商品名称:")),inname);
    in_storage->addRow(new QLabel(tr("商品数量")),incount);
    in_storage->addRow(new QLabel(tr("商品价格")),inprice);
    in_storage->addRow(new QLabel(tr("商品备注:")),inremark);
    in_storage->addRow(new QLabel(),in_submit);
    in_storage->setMargin(20);
  //-------------------------出库----------------------
    outstorage=new QGroupBox(tr("出库"));
    QFormLayout *out_storage=new QFormLayout(outstorage);
    outcount=new QSpinBox();
    outcount->setMaximum(10000);
    outcount->setMinimumWidth(100);
    outcount->setMaximumWidth(100);
    QPushButton *out_submit=new QPushButton(tr("出库"));
    out_submit->setMaximumWidth(50);
    outname=new QLineEdit();
    outremark=new QLineEdit();
    outid=new QLineEdit();
    outname->setFixedWidth(200);
    outremark->setFixedWidth(200);
    outid->setFixedWidth(200);
    out_storage->addRow(new QLabel(tr("商品编号:")),outid);
    out_storage->addRow(new QLabel(tr("商品名称:")),outname);
    out_storage->addRow(new QLabel(tr("商品数量")),outcount);
    out_storage->addRow(new QLabel(tr("商品备注:")),outremark);
    out_storage->addRow(new QLabel(),out_submit);
    out_storage->setMargin(20);
    //----------------系统设置界面----------------------------
     systemset=new QGroupBox(tr("系统设置"));//----初始化系统设置窗口窗口---------------------------
     //systemset->setStyleSheet("#bbbb{border-image:url(:/images/bwl.jpg);}");
     //systemset->setObjectName(QString::fromUtf8("bbbb"));
     stack=new QStackedWidget(this);//堆栈空间创建
     QWidget *widget1=new QWidget;//--//-----------设置功能stack堆栈窗口布局以及实现------第1页 常规-----------------
     //QLabel *pagename1=new QLabel(tr("常规设置"));
     QCheckBox *Cqidong=new QCheckBox(tr("开机自动启动软件"));//自动启动checkbox
     QRadioButton *Rbut1=new QRadioButton(tr("默认尺寸"));
     QRadioButton *Rbut2=new QRadioButton(tr("上次关闭时尺寸"));
     QWidget *but=new QWidget;//QRadioButton 控件化 这样只能选择一个button
     Rbut1->setChecked(true);
     QHBoxLayout *radiobutlayout=new QHBoxLayout(but);
     radiobutlayout->addWidget(Rbut1);
     radiobutlayout->addWidget(Rbut2);
     radiobutlayout->setMargin(0);
     radiobutlayout->setAlignment(Qt::AlignLeft);
     QComboBox *Lselect=new QComboBox;
     Lselect->setFixedWidth(120);
     Lselect->addItem(tr("-选择语言-"));
     Lselect->addItem(tr("中文"));
     Lselect->addItem(tr("英文"));
     QRadioButton *Rbut3=new QRadioButton(tr("托盘"));
     QRadioButton *Rbut4=new QRadioButton(tr("任务栏"));
     QRadioButton *Rbut5=new QRadioButton(tr("退出"));
     QRadioButton *Rbut6=new QRadioButton(tr("托盘"));
     QWidget *but1=new QWidget;
     Rbut3->setChecked(true);
     QHBoxLayout *radiobutlayout1=new QHBoxLayout(but1);
     radiobutlayout1->addWidget(Rbut3);
     radiobutlayout1->addWidget(Rbut4);
     radiobutlayout1->setMargin(0);
     radiobutlayout1->setAlignment(Qt::AlignLeft);
     QWidget *but2=new QWidget;
     Rbut6->setChecked(true);
     QHBoxLayout *radiobutlayout2=new QHBoxLayout(but2);
     radiobutlayout2->addWidget(Rbut6);
     radiobutlayout2->addWidget(Rbut5);
     radiobutlayout2->setMargin(0);
     radiobutlayout2->setAlignment(Qt::AlignLeft);
     QFormLayout *layout1=new QFormLayout;
     layout1->addRow(new QLabel(tr("启动")));
     layout1->addRow(Cqidong);
     layout1->addRow(new QLabel(tr("启动时窗口尺寸")));
     layout1->addRow(but);
     layout1->addRow(new QLabel(tr("语言设置")));
     layout1->addRow(new QLabel(tr("语言区域")),Lselect);
     layout1->addRow(new QLabel(tr("最小化设置")));
     layout1->addRow(but1);
     layout1->addRow(new QLabel(tr("程序关闭后")));
     layout1->addRow(but2);
     widget1->setLayout(layout1);
     stack->addWidget(widget1);
     QWidget *widget2=new QWidget;//------------------------第2页--界面设置----------
     QPushButton *colorbut=new QPushButton(tr("调色板"));
     colorbut->setFixedWidth(120);
     QPushButton *pifu=new QPushButton(tr("换肤"));
     pifu->setFixedWidth(120);
     QComboBox *Fsize=new QComboBox;//设置字体的大小
     Fsize->setFixedWidth(120);
     Fsize->addItem("10");
     Fsize->addItem("12");
     QComboBox *Ustyle=new QComboBox;//设置字体的大小
     Ustyle->addItem("字体类型");
     Ustyle->addItem("字体类型");
     Ustyle->setFixedWidth(120);
     QFormLayout *layout2=new QFormLayout;
     layout2->addRow(new QLabel(tr("用户界面")));
     layout2->addRow(new QLabel(tr("字体")),Ustyle);
     layout2->addRow(new QLabel(tr("换肤")),pifu);
     layout2->addRow(new QLabel(tr("设置界面")));
     layout2->addRow(new QLabel(tr("大小")),Fsize);
     layout2->addRow(new QLabel(tr("颜色")),colorbut);
     widget2->setLayout(layout2);
     stack->addWidget(widget2);
     QWidget  *widget3=new QWidget;//----------------------------第3页 用户-------------
     QLineEdit *username=new QLineEdit;
     username->setFixedWidth(120);
     QPushButton *xiugai=new QPushButton(tr("确认修改"));
     xiugai->setFixedWidth(120);
     QPushButton *dateremove=new QPushButton(tr("确定"));
     dateremove->setFixedWidth(120);
     QRadioButton *Rbut7=new QRadioButton(tr("可编辑"));//表格编辑的是否选项
     QRadioButton *Rbut8=new QRadioButton(tr("不可编辑"));
     QWidget *but3=new QWidget;
     Rbut7->setChecked(true);
     QHBoxLayout *radiobutlayout3=new QHBoxLayout(but3);
     radiobutlayout3->addWidget(Rbut7);
     radiobutlayout3->addWidget(Rbut8);
     radiobutlayout3->setMargin(0);
     radiobutlayout3->setAlignment(Qt::AlignLeft);
     QFormLayout *layout3=new QFormLayout;
     layout3->addRow(new QLabel(tr("用户帐号")));
     layout3->addRow(new QLabel(tr("当前用户")),new QLabel(tr("Administrator")));
     layout3->addRow(new QLabel(tr("修改用户名")),username);
     layout3->addRow(new QLabel(),xiugai);
     layout3->addRow(new QLabel(tr("用户表格")));
     layout3->addRow(but3);
     layout3->addRow(new QLabel(tr("重置用户数据及资料")));
     layout3->addRow(new QLabel(tr("点击将重置数据:")),dateremove);
     widget3->setLayout(layout3);
     stack->addWidget(widget3);
     QWidget *widget4=new QWidget;//第4页布局
     QFormLayout *layout4=new QFormLayout;
     widget4->setLayout(layout4);
     stack->addWidget(widget4);
     QWidget *widget5=new QWidget;//-------------第5页布局--更新------------------------
     QCheckBox *updata=new QCheckBox(tr("在通知区域中显示提示更新信息"));
     QPushButton *checkupdata=new QPushButton(tr("现在检查更新"));
     QPushButton *updataconfig=new QPushButton(tr("更新配置"));
     checkupdata->setFixedWidth(100);
     updataconfig->setFixedWidth(100);
     QFormLayout *layout5=new QFormLayout;
     layout5->addRow(new QLabel(tr("软件访问")));
     layout5->addRow(updata);
     layout5->addRow(new QLabel(tr("web更新")));
     layout5->addRow(checkupdata,updataconfig);
     widget5->setLayout(layout5);
     stack->addWidget(widget5);
     QWidget *widget6=new QWidget;//----------------第6页------------------------------
     QLabel *aboutthis=new QLabel(tr("XX仓库管理系统"));
     aboutthis->setAlignment(Qt::AlignCenter);//居中
     QPushButton  *but6=new  QPushButton(tr("关于"));
     but6->setFixedWidth(200);
     connect(but6,SIGNAL(clicked()),this,SLOT(about()));
     QHBoxLayout *layout6_1=new QHBoxLayout;
     layout6_1->addStretch();
     layout6_1->addWidget(but6);
     layout6_1->addStretch();
     QVBoxLayout *layout6=new QVBoxLayout;
     layout6->addWidget(aboutthis);
     layout6->setSpacing(10);
     layout6->addLayout(layout6_1);
     layout6->setMargin(10);
     widget6->setLayout(layout6);
     stack->addWidget(widget6);
     listwidget=new QListWidget;   // --------------------声明设置listwidget列表---------------
    // listwidget->setObjectName(QString::fromUtf8("aaaa"));
     listwidget->setSpacing(20);  //设置QListWidget中的单元项的间距
     listwidget->setMovement(QListView::Static); //设置QListWidget中的单元项不可被拖动
     listwidget->setResizeMode(QListView::Adjust);
     listwidget->setViewMode(QListView::IconMode);//设置QListWidget的显示模式
     listwidget->setFixedWidth(100);//设置控件宽度
     listwidget->setCurrentRow(0);
      listwidget->setStyleSheet("background:transparent");//控件背景透明化
    // listwidget->setStyleSheet("#aaaa{border-image:url(:/images/bwl.jpg);}");
     QString a[6]={":/images/changgui.png",":/images/jiemian.png",":/images/yonghu.png",":/images/wangluo.png",":/images/gengxing.png",":/images/guanyu1.png"};//图片路径
      QString b[6]={"常规","界面","用户","网络","更新","关于"};
      for(int i=0;i<6;i++)
     {
      item= new QListWidgetItem(QIcon(a[i]),b[i]);
      //item->setSizeHint(QSize(30,30));            //设置单元项的宽度和高度
      item->setTextColor(Qt::blue);
      //listwidget->setIconSize(QSize(450,250));
      listwidget->insertItem(i,item);
      }//添加listwidget里图片与名称

     QHBoxLayout *setlayout=new QHBoxLayout(systemset);
     setlayout->addWidget(listwidget);
     setlayout->addWidget(stack);

     //QHBoxLayout *mainlayout=new QHBoxLayout(this);
     //mainlayout->addWidget(systemset);
     connect(listwidget,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));

    //----------------修改密码界面------------------
    pswstorage=new QGroupBox(tr("修改密码"));
    QFormLayout *psw_storage=new QFormLayout(pswstorage);
    oldpassw=new QLineEdit();
    passw=new QLineEdit();
    surepassw=new QLineEdit();
    passw->setFixedWidth(100);
    surepassw->setFixedWidth(100);
    oldpassw->setFixedWidth(100);
    QPushButton *password_submit=new QPushButton(tr("确定"));
    password_submit->setMaximumWidth(50);
   // radio=new QRadioButton("是否显示密码明文?");
    oldpassw->setEchoMode(QLineEdit::Password);
    passw->setEchoMode(QLineEdit::Password);
    surepassw->setEchoMode(QLineEdit::Password);
    psw_storage->addRow(new QLabel(tr("登录用户")),new QLabel(tr("  Administrator")));
    psw_storage->addRow(new QLabel(tr("旧　密码")),oldpassw);
    psw_storage->addRow(new QLabel(tr("重置密码")),passw);
    psw_storage->addRow(new QLabel(tr("确认密码")),surepassw);
    //psw_storage->addRow(new QLabel(),radio);
    psw_storage->addRow(new QLabel(),password_submit);
    psw_storage->setMargin(20);
    //----------------查询功能界面---------------------
    findstorage=new QGroupBox(tr("查询"));
    QFormLayout *find_storage=new QFormLayout(findstorage);
    findedit=new QLineEdit();
    QPushButton *find_submit=new QPushButton(tr("查询"));
    find_submit->setMaximumWidth(50);
    findedit->setFixedWidth(100);
    find_storage->addRow(new QLabel(tr("查询商品：")),findedit);
    find_storage->addRow(new QLabel(),find_submit);
    find_storage->setMargin(20);
    //-----------------销售额模块 界面---------------
    salestorage=new QGroupBox(tr("销售额"));
    salemodel = new QStandardItemModel(12, 2, this);
    salemodel->setHeaderData(0, Qt::Horizontal, tr("月份"));
    salemodel->setHeaderData(1, Qt::Horizontal, tr("销售额"));
    QTableView *saletable=new QTableView(this);
    pieChart=new PieView;
    saletable->setModel(salemodel);
    pieChart->setModel(salemodel);
    QPushButton *salebut=new QPushButton(tr("更新数据"));
    //QItemSelectionModel *selectionModel = new QItemSelectionModel(salemodel);
    //saletable->setSelectionModel(selectionModel);
   // pieChart->setSelectionModel(selectionModel);
    QHeaderView *headerView = saletable->horizontalHeader();
    headerView->setStretchLastSection(true);
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(saletable);
    splitter->addWidget(pieChart);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    QHBoxLayout *sale_storage1=new QHBoxLayout;
    sale_storage1->addWidget(saletable);
    sale_storage1->addWidget(pieChart);
    QHBoxLayout *sale_storage2=new QHBoxLayout;
    sale_storage2->addStretch();
    sale_storage2->addWidget(salebut);
    QVBoxLayout  *sale_storage=new QVBoxLayout(salestorage);
     sale_storage->addLayout(sale_storage1);
     sale_storage->addLayout(sale_storage2);

    //-----------------做整体布局-------------------
    QGroupBox *window=new QGroupBox();
    QHBoxLayout *layout=new QHBoxLayout(window);
    layout->addWidget(menu);
    layout->addWidget(table);
    layout->addWidget(instorage);
    layout->addWidget(outstorage);
    layout->addWidget(pswstorage);
    layout->addWidget(findstorage);
    layout->addWidget(systemset);
    layout->addWidget(salestorage);
    layout->setStretchFactor(menu,1);
    layout->setStretchFactor(table,5);
    layout->setStretchFactor(instorage,5);
    layout->setStretchFactor(outstorage,5);
    layout->setStretchFactor(pswstorage,5);
    layout->setStretchFactor(findstorage,5);
    layout->setStretchFactor(systemset,5);
    layout->setStretchFactor(salestorage,5);
    setCentralWidget(window);
    instorage->hide();
    outstorage->hide();
    pswstorage->hide();
    findstorage->hide();
    systemset->hide();
    salestorage->hide();
   //-------------信号与槽:菜单栏事件处理------------------------------------
    connect(menu1_1, SIGNAL(clicked()),this, SLOT(menu1_1click()));//鼠标左键注册
    connect(menu1_2, SIGNAL(clicked()),this, SLOT(menu1_2click()));//鼠标左键注册
    connect(menu1_3, SIGNAL(clicked()),this, SLOT(menu1_3click()));//鼠标左键注册
    connect(menu4_1, SIGNAL(clicked()),this, SLOT(menu4_1click()));//鼠标左键注册
    connect(menu4_2, SIGNAL(clicked()),this, SLOT(menu4_2click()));//鼠标左键注册
    connect(menu3_1, SIGNAL(clicked()),this, SLOT(menu3_1click()));//鼠标左键注册
    connect(menu1_4, SIGNAL(clicked()),this, SLOT(menu1_4click()));//鼠标左键注册
    connect(menu2_0, SIGNAL(clicked()),this, SLOT(menu2_0click()));//鼠标左键注册
    connect(menu2_3, SIGNAL(clicked()),this, SLOT(menu2_3click()));//鼠标左键注册
    connect(in_submit, SIGNAL(clicked()),this, SLOT(in()));//入库操作
    connect(out_submit, SIGNAL(clicked()),this, SLOT(out()));//出库操作
    connect(menu3_2,SIGNAL(clicked()),this,SLOT(menu3_2click()));
    connect(menu3_1,SIGNAL(clicked()),this,SLOT(menu3_1click()));//
    connect(menu3_5,SIGNAL(clicked()),this,SLOT(menu3_5click()));//提交事务
    connect(menu3_0,SIGNAL(clicked()),this,SLOT(menu3_0click()));//添加商品
    connect(menu3_3,SIGNAL(clicked()),this,SLOT(menu3_3click()));//升序
    connect(menu3_4,SIGNAL(clicked()),this,SLOT(menu3_4click()));//降序
    connect(menu3_6,SIGNAL(clicked()),this,SLOT(menu3_6click()));//撤销
    connect(password_submit,SIGNAL(clicked()),this,SLOT(updatapsw()));//密码重置
    connect(find_submit,SIGNAL(clicked()),this,SLOT(Findstorage()));//查询功能
    connect(salebut,SIGNAL(clicked()),this,SLOT(opensaleFile()));//
    //------------piture软件界面--------------------
    QPixmap pi(":/images/bwl.jpg");
    QPalette pa;
    pa.setBrush(QPalette::Background,QBrush(pi));
    setPalette(pa);
}

//-------------------入库操作-----------------------
void storage::in()
{
    QString no=inid->text();
    QString name=inname->text();
    QString count=incount->text();
    QString price=inprice->text();
    QString remark=inremark->text();
    QSqlQuery query;
    QString sql;
    sql="select * from goods where name='";
    sql=sql+name;
    sql=sql+"'";
    query.exec(sql);
    if(query.next())
    {
        int f=atoi(count.toLatin1());
        f=f+query.value(3).toInt();
        sql="update goods set count=";
        sql=sql+QString::number(f);
        sql=sql+" where name='";
        sql=sql+name;
        sql=sql+"'";
    }
    else{
        sql="insert into goods(id,name,count,price,remark)values(";
        sql=sql+no;
        sql=sql+",'";
        sql=sql+name;
        sql=sql+"',";
        sql=sql+count;
        sql=sql+",'";
        sql=sql+price;
        sql=sql+"','";
        sql=sql+remark;
        sql=sql+"')";
    }
    if(query.exec(sql) && !inname->text().isEmpty() && !incount->text().isEmpty() && !inprice->text().isEmpty() && !inid->text().isEmpty())
    {
        QMessageBox::information(NULL,tr("入库成功"),tr("入库操作成功"));
    }
    else
    {
        QMessageBox::information(NULL,tr("入库失败"),tr("商品名称输入错误，入库操作失败"));
    }
   model->submitAll();
   table->show();
   instorage->hide();




}
//------------------------------出库操作---------------------------
void storage::out()
{   int price;
    QString name=outname->text();
    QString count=outcount->text();
    //QString remark=outremark->text();//这个remark是打算做记录的
    QSqlQuery query;
    QString sql;
    sql="select * from goods where name='";
    sql=sql+name;
    sql=sql+"'";
    query.exec(sql);
    if(query.next() &&!outname->text().isEmpty())
    {
        int f=atoi(count.toLatin1());
        f=query.value(3).toInt()-f;
        price=query.value(4).toInt();
        if(f<0)
        {
            QMessageBox::information(NULL,tr("出库失败"),tr("仓库货源不足"));
        }

             sql="update goods set count=";
              sql=sql+QString::number(f);
              sql=sql+" where name='";
              sql=sql+name;
              sql=sql+"'";
              if(query.exec(sql))
             {
               QMessageBox::information(NULL,tr("出库成功"),tr("出库操作成功"));
             }
             else
             {
               QMessageBox::information(NULL,tr("出库失败"),tr("出库操作失败"));
             }
        }
       else
       {
        QMessageBox::information(NULL,tr("出库失败"),tr("仓库没有这个存货!"));
       }

    model->submitAll();//出库完提交事件
    table->show();
    outstorage->hide();
    //------------------------------出库时对应的销售额更新模块------------------------
     int y;
     QDateTime datetime=QDateTime::currentDateTime();
     y=datetime.date().month();//定位当前月份
     //qDebug()<<"当前的月份为:";
     //qDebug()<<y;
    QString ofileName ="qtdata.cht";//打开当前文件寻找第（几月）行
    QFile ofile(ofileName);
    if (!ofile.open(QFile::ReadOnly | QFile::Text))
            return;
    QTextStream ostream(&ofile);
    QString line;
    QString save[12];
    int i;
    int j;
    for( int k=0;k<12;k++)
    {
    i=0;
    j=0;
    char n[10]={'0'};//初始化数组 用于存放销售额字段
    line=ostream.readLine();//读取行数
    QByteArray ba = line.toLatin1();
    char *m = ba.data();//将QString听转换为QChar
    while(*(m+i)!=',')//跳过第一个月份字段
       i++ ;

       i++;
    while(*(m+i)!=',')//读取第二个字段
    {
        n[j]= *(m+i);
        j++;
        i++;
    }
     QString lastdata = QString(QLatin1String(n));//char转换字符串
     save[k]=lastdata;//存放最终结果
     //qDebug()<<save[k];
    }

    int result;//得出的结果为已销售的总价格
    result=save[y-1].toInt();//将最后结果转换为整形
    int currdata=atoi(count.toLatin1());//将数量转为int型
    result+=currdata * price;//累加总销售额
    ofile.close();
    //-----------------------------------------------------

    QString salemonth[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    QString salecolor[12]={"#99e600","#99cc00","#99b300","#9f991a","#a48033","#a9664d","#ae4d66","#b33380","#a64086","#994d8d","#8d5a93","#806699"};
    QString fileName ="qtdata.cht";
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return ;
    QTextStream stream(&file);
    for (int row = 0; row < 12; row++)
    {

        QStringList pieces;
        if(row==y-1)//寻找当前月份所在的字段
        {
        pieces.append(salemonth[row]);
        pieces.append(QString::number(result));
        pieces.append(salecolor[row]);
        }
        else
        {
        pieces.append(salemonth[row]);
        pieces.append(save[row]);
        pieces.append(salecolor[row]);
        }
        stream << pieces.join(',') << "\n";
    }

    file.close();
}

void storage::updatapsw()//修改用户登录密码
{
      db2 =QSqlDatabase::addDatabase("QSQLITE", "db2");
      db2.setDatabaseName("nbut.zh"); // 数据库名与路径, 此时是放在同目录下
      bool open=db2.open(); // 连接数据库, 然后就可以使用了
      if(open) qDebug()<<"db2 SQL connect ok!";//测试数据库是否已经成功打开*/
      QSqlQuery query(db2);
      query.exec("select pwd from passw");
      query.next();
      if(oldpassw->text().isEmpty())
            QMessageBox::warning(this, tr("请输入密码"), tr("请输入旧密码和新密码"), QMessageBox::Ok);
        else if(oldpassw->text()!= query.value(0).toString())
        {
            QMessageBox::warning(this, "密码错误", tr("输入的旧密码错误"), QMessageBox::Ok);
            oldpassw->setFocus();
        }
        else
        {
            if(passw->text() == surepassw->text())
            {
                QString newPassword =passw->text();
                query.exec(QString("update passw set pwd=%1").arg(newPassword));//更新密码
               // query.exec("update passw set pwd = :pwd");
               // query.bindValue(":pwd", newPassword);
                qDebug()<<query.value(0).toString();
                QMessageBox::information(this, tr("修改密码"), tr("修改密码成功！"), QMessageBox::Ok);
            }
            else
                QMessageBox::warning(this, tr("修改密码失败"), tr("新密码两次输入不一致！"), QMessageBox::Ok);
        }
}

void storage::Findstorage()
{

   QString name =findedit->text();
   QString sql;
   sql="name='";
   sql=sql+name;
   sql=sql+"'";
   model->setFilter(sql);
   model->select();

}
//-------------------关于事件------------------------------
void storage::about()
{
    QMessageBox::about(this, tr("关于软件"),tr("仓管系统关于功能暂未开发"));
}



void storage::daochuE()
{

    QMessageBox::about(this, tr("导出"),tr("此功能暂未开发"));
}
//-----------------------查找窗口---------------------

void storage::enableedit()
{
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}

void storage::ableedit()//表可编辑
{
    table->setEditTriggers(QAbstractItemView::DoubleClicked);
}

void storage::tooltri()
{
     if(toolbar1->isMovable())
      {
        toolbar1->setMovable(false);
        toolbar2->setMovable(false);
        toolbar3->setMovable(false);
      }
     else
     {
         toolbar1->setMovable(true);
         toolbar2->setMovable(true);
         toolbar3->setMovable(true);
     }
}




void storage::opensaleFile()//更新销售额图表
{
    QString fileName="qtdata.cht";
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;

    QTextStream stream(&file);
    QString line;

    salemodel->removeRows(0, salemodel->rowCount(QModelIndex()), QModelIndex());

    int row = 0;
    do {
        line = stream.readLine();
        if (!line.isEmpty()) {
            salemodel->insertRows(row, 1, QModelIndex());

            QStringList pieces = line.split(",", QString::SkipEmptyParts);
            salemodel->setData(salemodel->index(row, 0, QModelIndex()),
                           pieces.value(0));
            salemodel->setData(salemodel->index(row, 1, QModelIndex()),
                           pieces.value(1));
            salemodel->setData(salemodel->index(row, 0, QModelIndex()),
                           QColor(pieces.value(2)), Qt::DecorationRole);
            row++;
        }
    } while (!line.isEmpty());

    file.close();
}

void storage::savesaleFile()
{

}
//---------------------托盘单双击事件------------------------
void storage::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
         {
         //点击托盘显示窗口
         case QSystemTrayIcon::Trigger:
          {
            showNormal();
            break;
          }
         //双击托盘关闭窗口
         case QSystemTrayIcon::DoubleClick:
         {
           //showNormal();
           hide();
           break;
         }
         default:
           break;
         }
}

void storage::readSettings()
{
    QSettings settings("QtProject", "storage Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void storage::writeSettings()//写应用程序相关设置
{
    QSettings settings("QtProject", "storage Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
void storage::menu1_1click()//更新表模块
{
    instorage->hide();
    outstorage->hide();
    table->show();
    pswstorage->hide();
    findstorage->hide();
    systemset->hide();
    salestorage->hide();
    model->setTable("goods");
    model->select();
    QString a[6]={"编号","名称","时间","数量","价格","备注"};
    for(int i=0;i<6;i++)
    {
      model->setHeaderData(i,Qt::Horizontal,a[i]);
    }

}
void storage::menu1_2click()//出库模块
{    inprice->clear();
    incount->clear();
    inid->clear();
    inname->clear();
    inremark->clear();
    instorage->show();
    outstorage->hide();
    table->hide();
    pswstorage->hide();
    findstorage->hide();
    systemset->hide();
    salestorage->hide();
}
void storage::menu1_3click()//出库模块
{
    outcount->clear();
    outid->clear();
    outname->clear();
    instorage->hide();
    outstorage->show();
    table->hide();
    pswstorage->hide();
    findstorage->hide();
    systemset->hide();
    salestorage->hide();
}
void storage::menu4_1click()//密码修改模块
{
    instorage->hide();
    outstorage->hide();
    table->hide();
    pswstorage->show();
    findstorage->hide();
    systemset->hide();
    salestorage->hide();
}
void storage::menu2_0click()//销售额模块接口
{
    instorage->hide();
    outstorage->hide();
    table->hide();
    pswstorage->hide();
    findstorage->hide();
    systemset->hide();
    salestorage->show();

}
void storage::menu4_2click()//系统设置接口
{
    showNormal();
    instorage->hide();
    outstorage->hide();
    table->hide();
    pswstorage->hide();
    findstorage->hide();
    systemset->show();
    salestorage->hide();
}

void storage::menu1_4click()//备忘录接口
{
    memorandum=new Memorandum;
    memorandum->setModal(true);//设置成非模态
    memorandum->show();

}
void storage::menu2_3click()//计算器显示
{
     Calculator *computer=new Calculator;
     computer->show();

}


void storage::menu3_2click()
{
//    int i=QMessageBox::warning(this,"请选择删除信息来源","您将删除信息到数据表中\n"
//    "请选择要删除的数据表",
//    tr("商品"),tr("客户"),tr("供货商"));

    int curRow = table->currentIndex().row();
     //获取选中的行
     model->removeRow(curRow);
     //删除该行
     int ok = QMessageBox::warning(this,tr("删除提示!"),tr("你确定删除当前行吗？"),  QMessageBox::Yes,QMessageBox::No);
     if(ok == QMessageBox::No)
     {
        model->revertAll(); //如果不删除，则撤销
     }
     else model->submitAll(); //否则提交，在数据库中删除该行

  }

void storage::menu3_1click()//查询功能
{

    instorage->hide();
    outstorage->hide();
    table->show();
    pswstorage->hide();
    findstorage->show();
    salestorage->hide();

}

void storage::menu3_5click()//提交
{
        model->database().transaction(); //开始事务操作
        if (model->submitAll())
          {
            model->database().commit(); //提交
          }
        else {
              model->database().rollback(); //回滚
              QMessageBox::warning(this, tr("错误"),tr("数据库错误"));
             }

}

void storage::menu3_0click()//增加一行表信息
{
//    QMessageBox::StandardButton ret;
//    QMessageBox box(QMessageBox::Warning,"请选择添加信息来源","您将添加信息到数据表中");
//    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel|QMessageBox::Save);
//    box.setButtonText (QMessageBox::Ok,QString("商品"));
//    box.setButtonText (QMessageBox::Cancel,QString("客户"));
//    box.setButtonText (QMessageBox::Save,QString("供货商"));
//    box.exec();
//    int i=QMessageBox::warning(this,"请选择添加信息来源","您将添加信息到数据表中\n"
//    "请选择要添加的数据表",
//    tr("商品"),tr("客户"),tr("供货商"));

//    if(i==0)
//    {
    int rowNum = model->rowCount(); //获得表的行数
    model->insertRow(rowNum); //添加一行

    model->setData(model->index(rowNum,0),rowNum+1);
    table->show();

}

void storage::menu3_3click()
{
    model->setSort(0,Qt::AscendingOrder); //id属性，即第0列，升序排列
    model->select();
}
void storage::menu3_4click()
{

    model->setSort(0,Qt::DescendingOrder);
    model->select();
}

void storage::menu3_6click()
{
    model->revertAll();
}
//----------------创建工具栏---------------------
void storage::createToolbar()
{
    toolbar1=addToolBar(tr("关于表"));
    toolbar1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolbar1->addAction(watchtable);
    toolbar1->addAction(saletable);
    toolbar1->addSeparator();
    toolbar1->addAction(customer);
    toolbar1->addAction(supplier);
    toolbar2=addToolBar(tr("未命名"));
    toolbar3=addToolBar(tr("系统"));
    toolbar3->addAction(sysset);
    toolbar3->addAction(locksyatem);
    toolbar3->addAction(toolmanage);
    toolbar3->addAction(aboutAct);
    toolbar3->addAction(exitsystem);
    toolbar3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    //toolbar1->setFixedHeight(45);//设置工具栏的长度
}
void storage::supplierabout()//停靠窗口显示
{
    dock->show();
    dockmodel->setTable("supplier");
    dockmodel->select();
    dockmodel->removeColumn(0);
    dockmodel->setHeaderData(0,Qt::Horizontal,"供货商姓名");
    dockmodel->setHeaderData(1,Qt::Horizontal,"供货商电话");
    dockmodel->setHeaderData(2,Qt::Horizontal,"供货商地址");


}

void storage::customerabout()
{
      dock->show();
      dockmodel->setTable("customer");
    dockmodel->select();
    dockmodel->removeColumn(0);
    dockmodel->setHeaderData(0,Qt::Horizontal,"客户姓名");
    dockmodel->setHeaderData(1,Qt::Horizontal,"客户电话");
    dockmodel->setHeaderData(2,Qt::Horizontal,"客户地址");

}

void storage::addData()
{
    int rowNum = dockmodel->rowCount(); //获得表的行数
    dockmodel->insertRow(rowNum); //添加一行

    dockmodel->setData(dockmodel->index(rowNum,0),rowNum+1);
    docktable->show();

}

void storage::deleteData()
{
    int curRow = docktable->currentIndex().row();
     //获取选中的行
     dockmodel->removeRow(curRow);
     //删除该行
     int ok = QMessageBox::warning(this,tr("删除提示!"),tr("你确定删除当前行吗？"),  QMessageBox::Yes,QMessageBox::No);
     if(ok == QMessageBox::No)
     {
        dockmodel->revertAll(); //如果不删除，则撤销
     }
     else dockmodel->submitAll(); //否则提交，在数据库中删除该行
}

void storage::commitData()
{
    dockmodel->database().transaction(); //开始事务操作
    if (dockmodel->submitAll())
      {
        dockmodel->database().commit(); //提交
      }
    else {
          dockmodel->database().rollback(); //回滚
          QMessageBox::warning(this, tr("错误"),tr("数据库错误"));
         }
}
void storage::creatdockwidget()
{
    dock=new QDockWidget(tr("最近更新资料如下"),this);
    dock->setFixedSize(320,520);
    //dock->setFeatures(QDockWidget::DockWidgetMovable);
   // dock->setAllowedAreas(Qt::RightDockWidgetArea);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);//停靠窗口拥有所有属性
    QGroupBox *dockwidget=new QGroupBox;
    docktable=new QTableView();
    QPushButton *addbut=new QPushButton(tr("添加信息"));
    QPushButton *deletebut=new QPushButton(tr("删除信息"));
    QPushButton *commitbut=new QPushButton(tr("提交"));
    connect(addbut,SIGNAL(clicked()),this,SLOT(addData()));
    connect(deletebut,SIGNAL(clicked()),this,SLOT(deleteData()));
    connect(commitbut,SIGNAL(clicked()),this,SLOT(commitData()));
    QHBoxLayout *butlayout=new QHBoxLayout;
    butlayout->addStretch();
    butlayout->addWidget(addbut);
    butlayout->addWidget(deletebut);
    butlayout->addWidget(commitbut);
    butlayout->addStretch();
    QVBoxLayout *docklayout=new QVBoxLayout(dockwidget);
    docklayout->addWidget(docktable);
    docklayout->addLayout(butlayout);
    dock->setWidget(dockwidget);

    dock->setStyleSheet("QDockWidget::title {background-color:transparent}");//背景透明
    //************

    dock->hide();
}

void storage::setStringData(QString user)//用来获取中间变量
{
     this->user=user;
     statusBar()->insertWidget(1,new QLabel(tr("当前管理用户:%1").arg(user)),1);
}
//----------------创建菜单栏---------------------------------
void storage::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("前往(G)"));
    fileMenu ->addAction(watchtable);
    fileMenu->addAction(ruku);
    fileMenu->addAction(chuku);
    editMenu = menuBar()->addMenu(tr("工具(T)"));
    editMenu->addAction(Find);
    editMenu->addAction(bwl);
    editMenu->addAction(computer);
    managemenu=menuBar()->addMenu(tr("管理(M)"));
    managemenu->addAction(saletable);
    managemenu->addAction(ableEdit);
    managemenu->addAction(enableEdit);
    systemenu=menuBar()->addMenu(tr("系统(S)"));
    systemenu->addAction(sysset);
    daorumenu=menuBar()->addMenu(tr("导出(D)"));
    daorumenu->addAction(daochu);
    menuBar()->addSeparator();
    helpMenu = menuBar()->addMenu(tr("帮助(H)"));
    helpMenu->addAction(aboutAct);

}

//-----------------------创建菜单事件----------------------
void storage::createActions()
{
    //---------前往菜单事件
    watchtable=new QAction(QIcon(":/images/new.png"),tr("商品表"),this);
    connect(watchtable,SIGNAL(triggered()),this,SLOT(menu1_1click()));
    watchtable->setStatusTip(tr("查看商品信息表(To check the goods information table)"));
    ruku=new QAction(tr("入库"),this);
    connect(ruku,SIGNAL(triggered()),this,SLOT(menu1_2click()));
    ruku->setStatusTip(tr("仓库加入商品"));
    chuku=new QAction(tr("出库"),this);
    connect(chuku,SIGNAL(triggered()),this,SLOT(menu1_3click()));
    chuku->setStatusTip(tr("仓库商品出货"));
    //----------工具菜单栏
    Find=new QAction(tr("查找"),this);
    Find->setStatusTip(tr("查找表格中的内容"));
    connect(Find,SIGNAL(triggered()),this,SLOT(menu3_1click()));
    bwl=new QAction(tr("备忘录"),this);
    bwl->setStatusTip(tr("便签：记事本"));
    connect(bwl,SIGNAL(triggered()),this,SLOT(menu1_4click()));
    computer=new QAction(tr("计算器"),this);
    computer->setStatusTip(tr("标准计算器 部件打开"));
    connect(computer,SIGNAL(triggered()),this,SLOT(menu2_3click()));
    //---------导出菜单栏工具
    daochu=new QAction(tr("导出"),this);
    daochu->setStatusTip(tr("导出为Excel形式的表格"));
    connect(daochu,SIGNAL(triggered()),this,SLOT(daochuE()));
   //-----------帮助 菜单栏事件
    aboutAct = new QAction(QIcon(":/images/guanyu.png"),tr("关于"), this);
    aboutAct->setStatusTip(tr("显示应用程序的信息(Show the application's About box)"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    //------------管理 菜单栏事件
    saletable=new QAction(QIcon(":/images/xiaoshoue2.png"),tr("销售表"),this);
    connect(saletable,SIGNAL(triggered()),this,SLOT(menu2_0click()));
    saletable->setStatusTip(tr("查看近一年月份销售额的情况"));
    supplier=new QAction(tr("供货商资料"),this);
    connect(supplier,SIGNAL(triggered()),this,SLOT(supplierabout()));
    supplier->setStatusTip(tr("查看所有供货商资料"));
    customer=new QAction(tr("客户资料"),this);
    customer->setStatusTip(tr("查看所有客户资料"));
    connect(customer,SIGNAL(triggered()),this,SLOT(customerabout()));
   // connect(customer,SIGNAL(triggered()),this,SLOT(客户资料接口));
    ableEdit=new QAction(tr("表格可编辑"),this);
    connect(ableEdit,SIGNAL(triggered()),this,SLOT(ableedit()));
    ableEdit->setStatusTip(tr("设置表可编辑"));
    enableEdit=new QAction(tr("表不可编辑"),this);
    connect(enableEdit,SIGNAL(triggered()),this,SLOT(enableedit()));
    enableEdit->setStatusTip(tr("设置表不可编辑"));
    //----------系统 菜单栏事件
    sysset=new QAction(QIcon(":/images/setting.png"),tr("系统设置"),this);
    connect(sysset,SIGNAL(triggered()),this,SLOT(menu4_2click()));
    locksyatem=new QAction(QIcon(":/images/xiumian.png"),tr("锁定系统"),this);
    //connect(locksyatem,SIGNAL(triggered()),this,SLOT(系统锁定模块));
    exitsystem=new QAction(QIcon(":/images/close.png"),tr("退出系统"),this);
    connect(exitsystem,SIGNAL(triggered()),this,SLOT(close()));
    toolmanage=new QAction(QIcon(":/images/shezhi.png"),tr("工具栏锁定切换"),this);
    connect(toolmanage,SIGNAL(triggered()),this,SLOT(tooltri()));
}


//-------------状态栏设置(初始化)-------------------------

void storage::statusUpDate()
{  //statusBar()->showMessage(tr("欢迎使用仓库管理系统"));
    QDateTime time = QDateTime::currentDateTime();
    //获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    //设置系统时间显示格式
    msgLabel->setText(str);
}
storage::~storage()
{
    db.close();
    db2.close();
    qDebug()<<this->user;
}
