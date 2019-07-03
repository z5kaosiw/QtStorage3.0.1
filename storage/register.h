#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Register *ui;
    QSqlDatabase db3;
    QPixmap *pi;
    QPalette *pa;
    int flag;
};

#endif // REGISTER_H
