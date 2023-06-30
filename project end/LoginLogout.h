#ifndef LOGINLOGOUT_H
#define LOGINLOGOUT_H

#include <QDialog>

namespace Ui {
class LoginLogout;
}

class LoginLogout : public QDialog
{
    Q_OBJECT

public:
    explicit LoginLogout(QWidget *parent = nullptr);
    QString getnCode();
    void setNCode(QString _nCode);
    ~LoginLogout();

private slots:


    void on_pushButton_clicked();

private:
    Ui::LoginLogout *ui;
    QString nCode;

};

#endif // LOGINLOGOUT_H
