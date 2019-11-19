#ifndef GETFRAMEFROMCAMERAWORKER_H
#define GETFRAMEFROMCAMERAWORKER_H

#include <QObject>
#include <QImage>

struct AVFrame;

/**
 * 从摄像头中捕获视频帧
 * 1. 然后用convert转换成RGB帧，构造一个QImage对象，用emit发送一个信号
 * 2. 用conver转换成YUV帧，并亚索成H.264帧，使用NDN传输接口发布到网络上
 * @brief The GetFrameFromCameraWorker class
 */
class GetFrameFromCameraWorker : public QObject
{
    Q_OBJECT
public:
    explicit GetFrameFromCameraWorker(QObject *parent = 0, const QString& prefix = "/producer", const QString& host = "", int port = 6363, int index = 0);
    ~GetFrameFromCameraWorker();
private:
    QString host;
    QString prefix;
    int port;
    int index;
signals:
    void getOneFrame(QImage image, int index);
public slots:
    void beginCaptureFrameFromCamera();
};

#endif // GETFRAMEFROMCAMERAWORKER_H
