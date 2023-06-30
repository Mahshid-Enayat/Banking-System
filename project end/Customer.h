#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QDialog>
#include "Person.h"
#include <QString>

namespace Ui {
class Customer;
}

class Customer : public QDialog , public Person
{
    Q_OBJECT

public:
    Customer(QWidget *parent = nullptr);
    Customer(QString _firstName,QString _lastName, QString _n_code, QString _phoneNumber,
             QString _landLine, QString _username, QString _password, int _year, int _month, int _day,QString _email);
    ~Customer();

private slots:
    void on_OpenNewAccount_clicked();

    void on_MyAccounts_clicked();

    void on_Logout_clicked();

    void on_editprofile_clicked();

    void on_enteryExitTime_clicked();

private:
    Ui::Customer *ui;
};

#endif // CUSTOMER_H
