#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <signin.h>
#include "QGraphicsPixmapItem"
#include "QGraphicsScene"
#define welcome ":/mybank.jpg"
#include"Login.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene * s=new QGraphicsScene(this);
    QGraphicsPixmapItem *p = new QGraphicsPixmapItem(QPixmap(welcome));
    s->addItem(p);
    ui->wel->setScene(s);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Login* h = new Login(this);
    this->close();
    h->show();
    return;

}

