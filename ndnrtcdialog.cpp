#include "ndnrtcdialog.h"
#include "ui_ndnrtcdialog.h"
#include <QPixmap>
#include <QDebug>
#include <globalconfig.h>
extern "C" {
#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
}

NDNRtcDialog::NDNRtcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NDNRtcDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("NDN多方视频会议系统演示");
    pGFFCWThread = new QThread(this);
    pGFFCW = new GetFrameFromCameraWorker(0, QString::fromStdString(GlobalConfig::contentPrefix),
                                          QString::fromStdString(GlobalConfig::host), GlobalConfig::port, 0);

    connect(ui->btnStartCaptureFromCamera, SIGNAL(clicked(bool)),
            pGFFCW, SLOT(beginCaptureFrameFromCamera()));
    connect(pGFFCWThread, SIGNAL(finished()), pGFFCW, SLOT(deleteLater()));
    connect(pGFFCW, SIGNAL(getOneFrame(QImage, int)), this, SLOT(presentOneFrame(QImage, int)));
    pGFFCW->moveToThread(pGFFCWThread);
    pGFFCWThread->start();

    // 初始化模态框
    // 添加一个远程的NDN节点
    addRemoteDlg = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(addRemoteDlg);
    addRemoteNameEdit = new QLineEdit();
    addRemoteNameEdit->text();
    addRemoteDlgBtn = new QPushButton();
    addRemoteDlgBtn->setText("确定");
    layout->addWidget(addRemoteNameEdit);
    layout->addWidget(addRemoteDlgBtn);
    addRemoteDlg->setModal(true);

    this->labels.append(ui->labelCamera);

    // 本机摄像头的画面算一个
    count++;

    av_register_all();
    avformat_network_init();
    avdevice_register_all();

    connect(addRemoteDlgBtn, SIGNAL(clicked(bool)), this, SLOT(onAddRemote()));
}

NDNRtcDialog::~NDNRtcDialog()
{
    delete ui;
}

void NDNRtcDialog::presentOneFrame(QImage image, int index)
{
    if(index < this->labels.size()) {
        this->labels[index]->setPixmap(QPixmap::fromImage(image));
    }
}

void NDNRtcDialog::on_btnAddRemote_clicked()
{

    addRemoteDlg->show();
}

void NDNRtcDialog::onAddRemote()
{
    addRemoteDlg->hide();
    const QString namePrefix = addRemoteNameEdit->text();
    QLabel *newLabel = new QLabel();
    this->labels.append(newLabel);
    QThread *newThread = new QThread(this);
    GetVideoStreamFromRemoteNDN *pGVSFE = new GetVideoStreamFromRemoteNDN(
                0, namePrefix, QString::fromStdString(GlobalConfig::host), GlobalConfig::port, this->count);
    connect(newThread, SIGNAL(finished()), pGVSFE, SLOT(deleteLater()));
    connect(pGVSFE, SIGNAL(getOneFrame(QImage, int)), this, SLOT(presentOneFrame(QImage, int)));
    connect(newThread, SIGNAL(started()), pGVSFE, SLOT(beginPullFromRemoteNDN()));
    pGVSFE->moveToThread(newThread);
    newThread->start();

    int row = (this->count / this->lineNum);
    int column = (this->count % this->lineNum);
    this->count++;

    ui->gridLayout->addWidget(newLabel, row, column, 1, 1);

    // 清空输入框
    addRemoteNameEdit->setText("");
}
