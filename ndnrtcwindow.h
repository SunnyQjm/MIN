#ifndef NDNRTCWINDOW_H
#define NDNRTCWINDOW_H

#include <QDialog>

namespace Ui {
class NDNRtcWindow;
}

class NDNRtcWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NDNRtcWindow(QWidget *parent = 0);
    ~NDNRtcWindow();

private:
    Ui::NDNRtcWindow *ui;
    GetFrameFromCameraWorker* pGFFCW;
    QThread* pGFFCWThread;

private slots:
    void presentOneFrame(QImage image);
};

#endif // NDNRTCWINDOW_H
