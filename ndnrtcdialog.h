#ifndef NDNRTCDIALOG_H
#define NDNRTCDIALOG_H

#include <QDialog>
#include <workers/getframefromcameraworker.h>
#include <workers/getvideostreamfromremotendn.h>
#include <QThread>
#include <QImage>
#include <QLineEdit>
#include <QPushButton>
#include <QList>
#include <QLabel>

namespace Ui {
class NDNRtcDialog;
}

class NDNRtcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NDNRtcDialog(QWidget *parent = 0);
    ~NDNRtcDialog();

private:
    Ui::NDNRtcDialog *ui;

    // 本机摄像头抓取
    GetFrameFromCameraWorker* pGFFCW;
    QThread* pGFFCWThread;

    // 当前显示几个画面
    int count = 0;
    int lineNum = 3;    // 每行最多几个画面
    QList<QLabel *> labels;

    // 添加远程节点模态框
    QDialog* addRemoteDlg;
    QLineEdit* addRemoteNameEdit;
    QPushButton* addRemoteDlgBtn;

private slots:
    void presentOneFrame(QImage image, int index);
    void on_btnAddRemote_clicked();
    void onAddRemote();
};

#endif // NDNRTCDIALOG_H
