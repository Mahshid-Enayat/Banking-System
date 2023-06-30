#ifndef CARDBYCARD_H
#define CARDBYCARD_H

#include <QDialog>

namespace Ui {
class CardByCard;
}

class CardByCard : public QDialog
{
    Q_OBJECT
private:
    Ui::CardByCard *ui;
    QString accNum;
    QString nCode;
    int index;
public:
    explicit CardByCard(QWidget *parent = nullptr);
    void increasReceiverBalance(long long price);
    void reduceSenderBalance(long long price);
    void setaccNum(QString _accNum);
    void setNCode(QString _NCode);
    void setIndex(int _index);
    QString getAccNum();
    QString getNCode();
    int getIndex();
    ~CardByCard();

private slots:

    void on_OKbtn_clicked();
};

#endif // CARDBYCARD_H
