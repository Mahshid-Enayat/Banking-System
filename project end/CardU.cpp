#include "CardU.h"
#include "ui_CardU.h"

#include <iostream>
#include <random>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include <QMessageBox>
#include<QIcon>
using namespace std;

inline long long int randomGen(long long int min_value  ,long long int max_value)
{
    rand();
    long long int random;
    random = rand() % (max_value - min_value)+ min_value;
    return random;
}

CardU::CardU(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardU)
{
    ui->setupUi(this);

    QIcon icn(":/card.png");
    this->setWindowIcon(icn);
}



CardU::~CardU()
{
    delete ui;
}

void CardU::setCardNumber()
{
    cardNumber = randomGen(1637102000000000 , 9999999999999999);
    return;
}

void CardU::setAccNumber(long long int _accNumber)
{
    accNumber=_accNumber;
    return;
}

void CardU::setCvv2()
{
    cvv2 = randomGen(100,999);
    return;
}

void CardU::setExpireDate()
{
    expireDate = expireDate.currentDate().addYears(5);
    return;
}

long long int  CardU::getCardNumber() const
{
    return cardNumber;
}

long long CardU::getAccNumber() const
{
    return accNumber;
}

int CardU::getCvv2() const
{
    return cvv2;
}

QDate CardU::getExpireDate() const
{
    return expireDate;
}

void CardU::showInfo()
{
    ui->cardNum->setText(QString::number(this->getCardNumber()));
    ui->accNum->setText(QString::number(this->getAccNumber()));
    ui->cvv->setText(QString::number(this->getCvv2()));
    ui->year->setText(QString::number(this->getExpireDate().year()));
    ui->month->setText(QString::number(this->getExpireDate().month()));
}

void CardU::on_ok_clicked()
{
    this->close();
}

