#include "logindialog.h"
#include "ui_logindialog.h"
#include "globalconfig.h"
#include "ndnrtcdialog.h"
#include <ndn-cxx/face.hpp>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    host(QString::fromStdString(GlobalConfig::host)),
    port(QString::number(GlobalConfig::port))
{

    ui->setupUi(this);
    this->setWindowTitle("NDN多方视频会议系统");
    ui->editHost->setText(host);
    ui->editPort->setText(port);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    if(this->contentPrefix.isEmpty()) {
        QMessageBox::information(this, "提示", "内容发布前缀不能为空，eg.: /qjm/producer");
        return;
    }
    GlobalConfig::contentPrefix = this->contentPrefix.toStdString();
    try {
        ndn::Face face(this->host.toStdString(), this->port.toStdString());
        face.processEvents();
        GlobalConfig::host = this->host.toStdString();
        GlobalConfig::port = this->port.toInt();
        NDNRtcDialog ndnRtcWindow;
        this->close();
        ndnRtcWindow.exec();
    } catch (boost::exception& e) {
        QMessageBox::critical(this, "错误", "无法连接到指定的NFD路由器，请检查地址是否正确！");
    }
}

void LoginDialog::on_editHost_textChanged(const QString &arg1)
{
    // host改变
    this->host = arg1;
}

void LoginDialog::on_editPort_textChanged(const QString &arg1)
{
    // port改变
    this->port = arg1;
}



void LoginDialog::on_editContentPrefix_textChanged(const QString &arg1)
{
    // 内容发布前缀改变
    this->contentPrefix = arg1;
}
