#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
    //void log();

private slots:
    void on_accountRequest_clicked();

    void on_pushButton_clicked();

    void on_bloCKaCCOUNT_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
