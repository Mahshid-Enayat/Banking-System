#ifndef BILL_H
#define BILL_H

#include <QDialog>

namespace Ui {
class Bill;
}

class Bill : public QDialog
{
    Q_OBJECT

public:
    explicit Bill(QWidget *parent = nullptr);
    ~Bill();

    void setaccNum(QString _accNum);
    QString getAccNum();
    void setNCode(QString _NCode);
    QString getNCode();
    void setIndex(int _index);
    int getIndex();

    void pushB(long long price);

private slots:
    void on_payButton_clicked();

private:
    Ui::Bill *ui;

    QString accNum;
    QString nCode;
    int index;
};

#endif // BILL_H
