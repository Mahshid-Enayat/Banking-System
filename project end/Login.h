#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_showhidePass_pressed();

    void on_showhidePass_released();

    void on_pushButton_3_clicked();

    void on_signup_clicked();

    void on_passwordLineEdit_textChanged(const QString &arg1);

    void on_userNameLineEdir_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
