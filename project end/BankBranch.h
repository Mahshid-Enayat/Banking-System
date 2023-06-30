#ifndef BANKBRANCH_H
#define BANKBRANCH_H

#include <QDialog>

namespace Ui {
class BankBranch;
}

class BankBranch : public QDialog
{
    Q_OBJECT

public:
    explicit BankBranch(QWidget *parent = nullptr);
    ~BankBranch();

private slots:
        void on_ok_clicked();

private:
    Ui::BankBranch *ui;
};

#endif // BANKBRANCH_H
