#include "BankBranch.h"
#include "ui_BankBranch.h"

#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include <QTableWidget>
#include "mainwindow.h"
using namespace std;

BankBranch::BankBranch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankBranch)
{
    ui->setupUi(this);
    QIcon icon(":/bankbranch.png");
    this->setWindowIcon(icon);

}

BankBranch::~BankBranch()
{
    delete ui;
}

void BankBranch::on_ok_clicked()
{
    this->close();
    return;
}

