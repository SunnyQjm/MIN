#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    QString host = "localhost";
    QString port = "6363";
    QString contentPrefix = "";
private slots:
    void on_pushButton_clicked();

    void on_editHost_textChanged(const QString &arg1);

    void on_editPort_textChanged(const QString &arg1);

    void on_editContentPrefix_textChanged(const QString &arg1);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
