#include "memorandum.h"
#include <QLabel>
#include <QtWidgets>
#include <QWidget>
#include <Qpalette>
#include <QFont>
#include <QMessageBox>

Memorandum::Memorandum()
{
    initialization();
    connect(StextEdit->document(),SIGNAL(contentsChanged()),this,SLOT(documentWasModified()));
    connect(but,SIGNAL(clicked(bool)),this,SLOT(reject()));
    setCurrentFile("");
    connect(but1,SIGNAL(pressed()),this,SLOT(saveAs()));
    connect(but2,SIGNAL(pressed()),this,SLOT(open()));

    QPixmap pi(":/images/bwl.jpg");
    QPalette pa;
    pa.setBrush(QPalette::Background,QBrush(pi));
    setPalette(pa);

}

Memorandum::~Memorandum()
{

}

void Memorandum::closeEvent(QCloseEvent *event)//关闭事件
{
  if (maybeSave()) {
      //writeSettings();
      event->accept();
  } else {
      event->ignore();
  }
}

void Memorandum::initialization()
{



 //------------控件始化---------------
    QFont ft; //字体
    QFont fm;
    QPalette pa; //色调
    pa.setColor(QPalette::WindowText,Qt::blue);
    ft.setPointSize(17);
    fm.setPointSize(10);
    fm.setBold(true);
    ft.setBold(true);
   /* registerinfo=new QLabel(tr("备忘录"));
    registerinfo->setFont(ft);
    registerinfo->setPalette(pa);
    registerinfo->setAlignment(Qt::AlignCenter);//居中*/
    QTimer *timer = new QTimer(this);//新建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpDate()));//关联定时器计满信号和相应的槽函数
    timer->start(1000);
    Slabel=new QLabel;//标签初始化
    bwtype=new QLabel(tr("备忘类型:"));
    bwtype->setFont(fm);
    systemtime=new QLabel(tr("系统时间:"));
    systemtime->setFont(fm);
    Ssystemtime=new QLabel();
    bwnr=new QLabel(tr("备忘内容:"));
    bwnr->setFont(fm);
    type=new QComboBox;
    type->addItem("--请选择--");
    type->addItem("商品备忘录");
    type->addItem("厂商备忘录");
    type->addItem("电话备忘录");
    type->addItem("销售备忘录");
    Slabel->setText(type->currentText().trimmed());
    connect(type,SIGNAL(currentTextChanged(QString)),Slabel,SLOT(setText(QString)));



    Slabel->setAlignment(Qt::AlignCenter);//标签居中
    Slabel->setFont(ft);
    Slabel->setPalette(pa);
    StextEdit=new QPlainTextEdit;//文本框初始化


     but1=new QPushButton(tr("保存"));//按钮
     but=new QPushButton(tr("退出"));
     but2=new QPushButton(tr("载入"));
     but1->setFixedSize(60,30);
     but->setFixedSize(60,30);
     but2->setFixedSize(60,30);

     QHBoxLayout *layout= new QHBoxLayout;
     layout->addWidget(bwtype);

     layout->addWidget(type);
     layout->addStretch();

     QHBoxLayout *layout1= new QHBoxLayout;
     layout1->addWidget(systemtime);
     layout1->addWidget(Ssystemtime);
     layout1->addStretch();

     QHBoxLayout *layout3= new QHBoxLayout;
     layout3->addWidget(bwnr);
     layout3->addWidget(StextEdit);
     QVBoxLayout *vlayout=new QVBoxLayout;
     vlayout->addLayout(layout);
     vlayout->addLayout(layout1);
     vlayout->addLayout(layout3);
     QHBoxLayout *butlayout= new QHBoxLayout;
     butlayout->addStretch();
     butlayout->addWidget(but2);
     butlayout->addWidget(but1);
     butlayout->addWidget(but);
     QVBoxLayout *mainlayout=new QVBoxLayout;
     mainlayout->addWidget(Slabel);
     mainlayout->addLayout(vlayout);
     mainlayout->addLayout(butlayout);
     setLayout(mainlayout);

}

bool Memorandum::maybeSave()
{
  if (StextEdit->document()->isModified())
  {
      QMessageBox::StandardButton ret;
      ret = QMessageBox::warning(this, tr("文档"),
                   tr("文档已被修改.\n"
                      "确定要保存文档吗?"),
                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
      if (ret == QMessageBox::Save)
          return save();
      else if (ret == QMessageBox::Cancel)
          return false;
  }
  return true;
}

void Memorandum::setCurrentFile(const QString &fileName)
{
  curFile = fileName;
  StextEdit->document()->setModified(false);
  setWindowModified(false);

  QString shownName = curFile;
  if (curFile.isEmpty())
  //connect(type,SIGNAL(currentTextChanged(QString)),this,SLOT(setWindowTitle(QString)));

  if (curFile.isEmpty())
    shownName ="新建备忘录.txt";

  setWindowFilePath(shownName);
  // setWindowTitle(QString("FileName[*] - XXXXX"));
}

bool Memorandum::saveFile(const QString &fileName)
{
  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
      QMessageBox::warning(this, tr("Application"),
                           tr("Cannot write file %1:\n%2.")
                           .arg(fileName)
                           .arg(file.errorString()));
      return false;
  }


  QTextStream out(&file);
#ifndef QT_NO_CURSOR
  QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
  out << StextEdit->toPlainText();
#ifndef QT_NO_CURSOR
  QApplication::restoreOverrideCursor();
#endif

  setCurrentFile(fileName);
  return true;
}

void Memorandum::loadFile(const QString &fileName)
{
  QFile file(fileName);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
      QMessageBox::warning(this, tr("Application"),
                           tr("Cannot read file %1:\n%2.")
                           .arg(fileName)
                           .arg(file.errorString()));
      return;
  }

  QTextStream in(&file);
#ifndef QT_NO_CURSOR
  QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
  StextEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
  QApplication::restoreOverrideCursor();
#endif

  setCurrentFile(fileName);
 // statusBar()->showMessage(tr("File loaded"), 2000);
}

void Memorandum::documentWasModified()
{
  setWindowModified(StextEdit->document()->isModified());
}

bool Memorandum::save()
{
  if (curFile.isEmpty()) {
      return saveAs();
  } else {
      return saveFile(curFile);
  }

}

bool Memorandum::saveAs()
{


QString fileName = QFileDialog::getSaveFileName(this,tr("Save sto"), ".",tr("sto files (*.sto)"));


 if (fileName.isEmpty())
   return false;

 return saveFile(fileName);

 /* QFileDialog dialog(this);
  dialog.setWindowModality(Qt::WindowModal);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  QStringList files;
  if (dialog.exec())
      files = dialog.selectedFiles();
  else
      return false;

  return saveFile(files.at(0));*/
}

void Memorandum::open()
{
  if (maybeSave()) {
      QString fileName = QFileDialog::getOpenFileName(this);
      if (!fileName.isEmpty())
          loadFile(fileName);
  }
}

void Memorandum::timeUpDate()
{
    QDateTime time = QDateTime::currentDateTime();
    //获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    //设置系统时间显示格式
    Ssystemtime->setText(str);
}

