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
    explicit GetPCMFromMicrophoneWorker(QObject *parent = 0);

signals:

public slots:
};

#endif // GETPCMFROMMICROPHONEWORKER_H
