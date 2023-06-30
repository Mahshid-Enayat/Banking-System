#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "CardU.h"
#include <QDateTime>
#include<QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include <QJsonValue>

class Account
{
private:

    int accNumber;
    QString type;
    long long int balance;
    QDateTime openAccDate;
    QDateTime calDateOfInterest;
    CardU card;
    bool enoughBalance;

protected:
    double interest;

public:
    Account();
    ~Account();
    void giveaccNumber();
    void setAccountNumber(int _accountNumber);
    void setType(QString _type);
    void setBalance(long long int _Balance);
    void setCalDateOfInterest(QDateTime _calDateOfInterest);
    void setInterest(double _interest);

    void setEnoughBalance(bool _n);
    bool getEnoughBalance();
    bool checkExistaccountNumber(QString _accNum);

    int getaccNumber() const;
    QString getType() const;
    long long int getBalance() const;
    QDateTime getOpenAccDate();
    QDateTime getCalDateOfInterest();
    double getInterest() const;
    CardU getCard() const;

     virtual long long int calculateInterest() =0;
     virtual void transferMoneyViaAccount(QString accNum,int _index, QString _nCode , long long int amount,QString _toaccountNum);

};

#endif // ACCOUNT_H
