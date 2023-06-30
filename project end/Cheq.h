#ifndef CHEQ_H
#define CHEQ_H

#include <QDialog>

namespace Ui {
class Cheq;
}

class Cheq : public QDialog
{
    Q_OBJECT

public:
    explicit Cheq(QWidget *parent = nullptr);
    ~Cheq();

    void setaccNum(QString _accNum);
        void setNCode(QString _NCode);
        QString getAccNum();
        QString getNCode();

private slots:

    void on_pushButton_clicked();

private:
    Ui::Cheq *ui;

    QString accNum;
       QString nCode;
};

#endif // CHEQ_H
