#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>

namespace Ui {
class Signin;
}

class Signin : public QDialog
{
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = nullptr);
    ~Signin();


private slots:

    void on_hideshowPass_pressed();
    void on_hideshowPass_released();

    void on_hideshowPass_2_pressed();
    void on_hideshowPass_2_released();

    void on_FirstName_textChanged(const QString &arg1);

    void on_LastName_textChanged(const QString &arg1);

    void on_Username_textChanged(const QString &arg1);

    void on_Password_textChanged(const QString &arg1);

    void on_confirm_textChanged(const QString &arg1);

    void on_Email_textChanged(const QString &arg1);

    void on_nextBtn_clicked();

private:
    Ui::Signin *ui;
};

#endif // SIGNIN_H
