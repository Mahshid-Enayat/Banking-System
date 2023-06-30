#ifndef LONGTERMACCOUNT_H
#define LONGTERMACCOUNT_H

#include "Account.h"

class LongTermAccount :public Account
{

public:
     LongTermAccount();
     ~LongTermAccount();
     virtual long long calculateInterest();
     virtual void transferMoneyViaAccount(QString accNum, int _index, QString _nCode, long long int amount, QString _toaccountNum);
};

#endif // LONGTERMACCOUNT_H
