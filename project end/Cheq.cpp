#include "Cheq.h"
#include "ui_Cheq.h"
#include <QIcon>


Cheq::Cheq(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cheq)
{
    ui->setupUi(this);
    QIcon i(":/cheque.png");
    this->setWindowIcon(i);
}

Cheq::~Cheq()
{
    delete ui;
}

void Cheq::setaccNum(QString _accNum)
{
    accNum = _accNum;
}

QString Cheq::getAccNum()
{
    return accNum;
}

void Cheq::setNCode(QString _NCode)
{
    nCode =_NCode;
}

QString Cheq::getNCode()
{
    return nCode;
}

void Cheq::on_pushButton_clicked()
{
  this->close();
}
