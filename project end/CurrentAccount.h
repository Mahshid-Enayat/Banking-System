#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H
#include <QDate>
#include "Account.h"


class CurrentAccount : public Account
{

public:
    CurrentAccount();
    ~CurrentAccount();


    virtual long long  calculateInterest();
    virtual void transferMoneyViaAccount(QString accNum, int _index, QString _nCode, long long int amount, QString _toaccountNum);
};

#endif // CURRENTACCOUNT_H
