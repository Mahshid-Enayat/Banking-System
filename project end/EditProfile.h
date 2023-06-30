#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QDialog>

namespace Ui {
class EditProfile;
}

class EditProfile : public QDialog
{
    Q_OBJECT

public:
    explicit EditProfile(QWidget *parent = nullptr);
    ~EditProfile();
    void setNCode(QString _nCode);
    QString getNCode();

private slots:
    void on_hideshowpass_released();

    void on_hideshowpass_pressed();

    void on_hideshowpass_2_pressed();

    void on_hideshowpass_2_released();

    void on_editBtn_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::EditProfile *ui;
    QString ncode;
};

#endif // EDITPROFILE_H
