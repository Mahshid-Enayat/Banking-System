#ifndef BUYNET_H
#define BUYNET_H

#include <QDialog>

namespace Ui {
class BuyNet;
}

class BuyNet : public QDialog
{
    Q_OBJECT

public:
    explicit BuyNet(QWidget *parent = nullptr);
    ~BuyNet();

    void setaccNum(QString _accNum);
    QString getAccNum();
    void setNCode(QString _NCode);
    QString getNCode();
    void setIndex(int _index);
    int getIndex();

    void pushB(long long int price);

private slots:
    void on_p1_clicked();

    void on_p2_clicked();

    void on_p3_clicked();

    void on_p4_clicked();

    void on_p5_clicked();

    void on_p6_clicked();

    void on_p7_clicked();

    void on_p8_clicked();

    void on_p9_clicked();

    void on_p10_clicked();

    void on_p11_clicked();

    void on_p12_clicked();

private:
    Ui::BuyNet *ui;

    QString accNum;
    QString nCode;
    int index;
};

#endif // BUYNET_H
