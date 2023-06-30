#ifndef MYACCOUNTS_H
#define MYACCOUNTS_H

#include <QDialog>
#include <iostream>
#include <QString>
#include "Account.h"
#include "ShortTermAccount.h"
#include "LongTermAccount.h"
#include "CurrentAccount.h"
#include "SavingAccount.h"

using namespace std;

namespace Ui {
class MyAccounts;
}

class MyAccounts : public QDialog
{
    Q_OBJECT

public:
    explicit MyAccounts(QWidget *parent = nullptr);
    ~MyAccounts();

    void setNCode(QString _nCode);
    QString getNCode();

    void start();

private slots:
    void on_next_clicked();

    void on_befor_clicked();

    void on_buyingNet_clicked();

    void on_requestCard_clicked();

    void on_bill_clicked();

    void on_CreditCharge_clicked();

    void on_Cheque_clicked();

    void on_transferByAccount_clicked();

    void on_loan_clicked();

private:
    Ui::MyAccounts *ui;

    QString ncode;
    int index;
};

#endif // MYACCOUNTS_H
