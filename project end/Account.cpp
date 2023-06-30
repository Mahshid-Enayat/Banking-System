#include "Account.h"
#include <iostream>
#include <random>
#include <QDateTime>
#include <QMessageBox>


using namespace std;

Account::Account()
{
    interest=0;
    openAccDate = QDateTime::currentDateTime();
}

Account::~Account()
{

}

inline long long int randomGen(long long int min_value  ,long long int max_value)
{
    rand();
    long long int random;
    random = rand() % (max_value - min_value)+ min_value;
    return random;
}

void Account::giveaccNumber()
{
    accNumber=randomGen(1000000,9999999);
    return;
}

void Account::setAccountNumber(int _accountNumber)
{
    accNumber = _accountNumber;
}

void Account::setType(QString _type)
{
    type=_type;
    return;
}

int Account::getaccNumber() const
{
    return accNumber;
}

QString Account::getType() const
{
    return type;
}

void Account::setBalance(long long _Balance)
{
    balance = _Balance;
    return;
}

void Account::setCalDateOfInterest(QDateTime _calDateOfInterest)
{
    calDateOfInterest = _calDateOfInterest;
    return;
}


void Account::setInterest(double _interest)
{
    interest=_interest;
    return;
}

long long Account::getBalance() const
{
    return balance;
}

QDateTime Account::getOpenAccDate()
{
    openAccDate=QDateTime::currentDateTime();
    return openAccDate;
}

QDateTime Account::getCalDateOfInterest()
{
    return calDateOfInterest;
}

double Account::getInterest() const
{
    return interest;
}

void Account::transferMoneyViaAccount(QString accNum, int _index, QString _nCode, long long int amount, QString _toaccountNum)
{
    return;
}

void Account::setEnoughBalance(bool _n)
{
    this->enoughBalance = _n;
}

bool Account::getEnoughBalance()
{
    return this->enoughBalance;
}

bool Account::checkExistaccountNumber(QString _accNum)
{
    QJsonArray arraySize;
    QFile file("D:/Accounts.json");
    file.open(QIODevice::ReadWrite);
    QJsonDocument d = QJsonDocument::fromJson(file.readAll());
    QJsonObject o = d.object();
    file.close();
    int flag =0;
    foreach(QJsonValue x ,o["accounts"].toArray())
    {
            arraySize=x["arrayOfMyAccounts"].toArray();
            for(int i=0;i<arraySize.size();i++)
            {
                if(_accNum ==QString::number((((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountNumber"].toInt()))
                    {flag=1;}}
    }
    if(flag==1)
    {
      return true;
    }
    else
    {
        return false;
    }
}
