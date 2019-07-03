#ifndef MEMORANDUM_H
#define MEMORANDUM_H
#include <QDialog>
#include <QtWidgets>
#include <QLabel>

class QLabel;


class Memorandum: public QDialog
{
  Q_OBJECT
public:
    Memorandum();
   ~Memorandum();
protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private:
         void initialization();
         bool maybeSave();
         void setCurrentFile(const QString &fileName);
         bool saveFile(const QString &fileName);
         void loadFile(const QString &fileName);

         QLabel *systemtime;
         QLabel *Slabel;
         QLabel *Ssystemtime;
         QLabel *bwtype;
         QLabel *bwnr;
         QLabel *addtime;
         QPushButton *but;
         QPushButton *but1;
         QPushButton *but2;
         QComboBox *type;
         QLineEdit *time;


         QPlainTextEdit *StextEdit;//备忘录
         QString curFile;
         QPixmap *pi;
         QPalette *pa;
private slots:
         void documentWasModified();
         bool save();
         bool saveAs();
         void open();
         void  timeUpDate();

};

#endif // MEMORANDUM_H
