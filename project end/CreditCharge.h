#ifndef CREDITCHARGE_H
#define CREDITCHARGE_H

#include <QDialog>

namespace Ui {
class CreditCharge;
}

class CreditCharge : public QDialog
{
    Q_OBJECT

public:
    explicit CreditCharge(QWidget *parent = nullptr);
    ~CreditCharge();

    void setaccNum(QString _accNum);
    QString getAccNum();
    void setNCode(QString _NCode);
    QString getNCode();
    void setIndex(int _index);
    int getIndex();

    void pushB(long long int price);

private slots:
    void on_buy_clicked();

private:
    Ui::CreditCharge *ui;

    QString accNum;
    QString nCode;
    int index;
};

#endif // CREDITCHARGE_H
