#include "LongTermAccount.h"
#include <iostream>
#include <QMessageBox>
using namespace std;


LongTermAccount::LongTermAccount()
{

}

LongTermAccount::~LongTermAccount()
{
    QDateTime currentDate;
    currentDate = QDateTime::currentDateTime();
    if(getCalDateOfInterest().daysTo(currentDate) < 90){
        int monthNum = getCalDateOfInterest().daysTo(currentDate) / 30;
        setInterest(0.1);
        for(int j =0; j < monthNum;j++)
            setBalance(getBalance() + (getBalance() * (getInterest())));

    }
}

long long LongTermAccount::calculateInterest(){

    QDateTime currentDate;
       currentDate = QDateTime::currentDateTime();
       if(getCalDateOfInterest().daysTo(currentDate) >= 90){

           int monthNum = getCalDateOfInterest().daysTo(currentDate) / 90;
           long long interest =0;
           for(int j =0; j < monthNum;j++)
              interest=( (getBalance() * (getInterest())))+interest;


           setCalDateOfInterest(getCalDateOfInterest().addMonths(monthNum));
           return interest;
       }
       return 0;

}

void LongTermAccount::transferMoneyViaAccount(QString accNum, int _index, QString _nCode, long long amount, QString _toaccountNum){

    QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"Error"," You can not transfer money via Longterm Account!");
    msg->addButton(QMessageBox::Ok);
    msg->show();
    return;

}
