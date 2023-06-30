#ifndef SHORTTERMACCOUNT_H
#define SHORTTERMACCOUNT_H

#include <QDate>
#include "Account.h"

class ShortTermAccount : public Account
{
private:


public:
    ShortTermAccount();
    ~ShortTermAccount();
    virtual void transferMoneyViaAccount(QString accNum, int _index, QString _nCode, long long amount, QString _toaccountNum);
    virtual long long calculateInterest();
};

#endif // SHORTTERMACCOUNT_H
