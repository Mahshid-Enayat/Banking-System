#ifndef BLOCKACCOUNT_H
#define BLOCKACCOUNT_H

#include <QDialog>

namespace Ui {
class BlockAccount;
}

class BlockAccount : public QDialog
{
    Q_OBJECT

public:
    explicit BlockAccount(QWidget *parent = nullptr);
    ~BlockAccount();


private slots:
    void on_okBtn_clicked();

private:
    Ui::BlockAccount *ui;

};

#endif // BLOCKACCOUNT_H
