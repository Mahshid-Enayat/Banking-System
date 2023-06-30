#include "Login.h"
#include "ui_Login.h"
#include "BankBranch.h"
#include "signin.h"
#include "Customer.h"
#include <QIcon>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QMessageBox>
#include "QGraphicsPixmapItem"
#include "QGraphicsScene"
#define Eye ":/eye.jpg"
#define LOGO ":/logo.jpg"
#include"Admin.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QIcon icon(":/login.png");
    this->setWindowIcon(icon);

    QGraphicsScene * s=new QGraphicsScene(this);
    QGraphicsPixmapItem *p = new QGraphicsPixmapItem(QPixmap(LOGO));
    s->addItem(p);
    ui->logoPicture->setScene(s);

    QPixmap eye(Eye);
    ui->showhidePass->setIcon(eye);
    return;
}

Login::~Login()
{
    delete ui;
    return;
}

void Login::on_showhidePass_pressed()
{
    ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    return;
}


void Login::on_showhidePass_released()
{
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->passwordLineEdit->setFocus();
    return;
}


void Login::on_pushButton_3_clicked()
{
    QFile f("D:/UserInfo.json");
    f.open(QIODevice::ReadWrite);
    QJsonDocument d = QJsonDocument::fromJson(f.readAll());
    QJsonObject o = d.object();
    f.close();
    short flag =0;
    foreach(QJsonValue x ,o["Users"].toArray())
    {
         if(x["username"].toString()==ui->userNameLineEdir->text())
         {
                if(x["password"].toString()==ui->passwordLineEdit->text())
                {
                    flag = 0;
                    Customer *cust = new Customer(x["firstName"].toString(),
                            x["lastName"].toString(),x["nCode"].toString(),x["phoneNumber"].toString(),
                            x["landline"].toString(),x["username"].toString(),x["password"].toString(),
                            x["year"].toInt(),x["month"].toInt(),x["day"].toInt(),x["email"].toString());

                    cust->show();
                    this->close();
                    break;
                }
                else
                {
                    flag = 0;
                    QMessageBox *msgWarning = new QMessageBox(QMessageBox::Warning,"Error","Your password is incorrect.",QMessageBox::Ok);
                    msgWarning->show();
                    connect(msgWarning,&QMessageBox::buttonClicked,msgWarning,&QMessageBox::deleteLater,Qt::QueuedConnection);

                }
                break;

            }

            else
            {
                flag =1;

            }

    }
if(flag==1)
   ui->label->setText("this username does not exist!");
}


void Login::on_signup_clicked()
{
    Signin *n=new Signin(this);
    n->show();
    return;
}


void Login::on_passwordLineEdit_textChanged(const QString &pass)
{
    if(ui->passwordLineEdit->text().isEmpty())
    {
         ui->label_3->clear();
    }
    else if(pass.contains(QChar(' ')))
    {
        ui->passwordLineEdit->backspace();
        ui->label_3->setText("Wrong!");
    }
    else
    {
       ui->label_3->clear();
    }
    return;
}


void Login::on_userNameLineEdir_textChanged(const QString &user)
{
    if(ui->userNameLineEdir->text().isEmpty())
    {
         ui->label->clear();
    }
    else if(user.contains(QChar(' ')))
    {
        ui->userNameLineEdir->backspace();
        ui->label->setText("Wrong!");
    }
    else
    {
       ui->label->clear();
    }
    return;
}


void Login::on_pushButton_5_clicked()
{
    this->close();
    return;
}


void Login::on_pushButton_4_clicked()
{
    BankBranch* B=new BankBranch(this);
    B->show();
    return;
}


void Login::on_pushButton_clicked()
{
    if(ui->userNameLineEdir->text()=="Admin" && ui->passwordLineEdit->text()=="adminramz")
    {
        Admin* admin = new Admin(this);
        admin->show();
    }
    else
    {
        QMessageBox *msgWarning = new QMessageBox(QMessageBox::Warning,"Error","You are not admin or your information is incorrect.",QMessageBox::Ok);
        msgWarning->show();
        connect(msgWarning,&QMessageBox::buttonClicked,msgWarning,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
}

