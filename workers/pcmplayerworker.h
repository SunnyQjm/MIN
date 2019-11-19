#ifndef PCMPLAYERWORKER_H
#define PCMPLAYERWORKER_H

#include <QObject>

/**
 * 从NDN网络中获取PCM裸流，并播放出来
 * @brief The PCMPlayerWorker class
 */
class PCMPlayerWorker : public QObject
{
    Q_OBJECT
public:
    explicit PCMPlayerWorker(QObject *parent = 0, const QString& prefix = "/comsumer", const QString& host = "", int port = 6363, int index = 0);
private:
    QString host;
    QString prefix;
    int port;
    int index;
signals:

public slots:
    void beginPlayerPCM();
};

#endif // PCMPLAYERWORKER_H
