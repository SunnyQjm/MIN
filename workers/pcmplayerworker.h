#ifndef PCMPLAYERWORKER_H
#define PCMPLAYERWORKER_H

#include <QObject>
#include "ndn_ffmpeg_rtc/helper/SDL2Helper.h"

/**
 * 从NDN网络中获取PCM裸流，并播放出来
 * @brief The PCMPlayerWorker class
 */
class PCMPlayerWorker : public QObject
{
    Q_OBJECT
public:
    explicit PCMPlayerWorker(QObject *parent = 0, const QString& prefix = "/comsumer", const QString& host = "", int port = 6363, int index = 0, SDL2Helper* sdl2Helper = nullptr);
private:
    QString host;
    QString prefix;
    int port;
    int index;
    SDL2Helper* sdl2Helper;
signals:

public slots:
    void beginPlayerPCM();
};

#endif // PCMPLAYERWORKER_H
