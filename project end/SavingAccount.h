#ifndef SAVINGACCOUNT_H
#define SAVINGACCOUNT_H

#include "Account.h"

class SavingAccount : public Account
{

public:
    SavingAccount();
    ~SavingAccount();
    virtual long long calculateInterest();
     virtual void transferMoneyViaAccount(QString accNum, int _index, QString _nCode, long long int amount, QString _toaccountNum);
};

#endif // SAVINGACCOUNT_H
