#ifndef GETPCMFROMMICROPHONEWORKER_H
#define GETPCMFROMMICROPHONEWORKER_H

#include <QObject>

/**
 * 从麦克风中抓取PCM裸流并发布出去
 * @brief The GetPCMFromMicrophoneWorker class
 */
class GetPCMFromMicrophoneWorker : public QObject
{
    Q_OBJECT
public:
    explicit GetPCMFromMicrophoneWorker(QObject *parent = 0, const QString& prefix = "/producer", const QString& host = "", int port = 6363, int index = 0);

private:
    QString host;
    QString prefix;
    int port;
    int index;
signals:

public slots:
    void beginCapturePCMFrameFromMicrophone();
};

#endif // GETPCMFROMMICROPHONEWORKER_H
