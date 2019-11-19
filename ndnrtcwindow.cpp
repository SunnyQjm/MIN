#include "ndnrtcwindow.h"
#include "ui_ndnrtcwindow.h"
#include <QPixmap>

NDNRtcWindow::NDNRtcWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NDNRtcWindow)
{
    ui->setupUi(this);
    pGFFCWThread = new QThread();
    pGFFCW = new GetFrameFromCameraWorker();

    connect(ui->btnStartCaptureFromCamera, SIGNAL(clicked(bool)),
            pGFFCW, SLOT(beginCaptureFrameFromCamera()));
    connect(pGFFCWThread, SIGNAL(finished()), pGFFCW, SLOT(deleteLater()));
    connect(pGFFCW, SIGNAL(getOneFrame(QImage)), this, SLOT(presentOneFrame(QImage)));
    pGFFCW->moveToThread(pGFFCWThread);
    pGFFCWThread->start();
}

NDNRtcWindow::~NDNRtcWindow()
{
    delete ui;
}

void MainWindow::presentOneFrame(QImage image)
{
    ui->labelCamera->setPixmap(QPixmap::fromImage(image));
}
