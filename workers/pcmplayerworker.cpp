#include "pcmplayerworker.h"
#include "ndn_ffmpeg_rtc/ndn_rtp/ndn_rtpc.h"

PCMPlayerWorker::PCMPlayerWorker(QObject *parent, const QString& prefix, const QString& host, int port, int index, SDL2Helper* sdl2Helper)
    : QObject(parent), prefix(prefix), host(host), port(port), index(index), sdl2Helper(sdl2Helper)
{

}

void PCMPlayerWorker::beginPlayerPCM()
{
    ndn_rtpc audioConsumer(this->prefix.toStdString() + "/audio", this->host.toStdString(), this->port);
//    SDL2Helper sdl2Helper(SDL_INIT_AUDIO);
//    sdl2Helper.setAudioSpecFreq(48000)
//            ->setAudioSpecFormat(AUDIO_S16SYS)
//            ->setAudioSpecChannels(2)
//            ->setAudioSpecSilence(0)
//            ->setAudioSpecSamples(1024)
//            ->openAudio()
//            ->pauseAudio(0);
    uint32_t recvLen;
    char buff[200000];
    while(true) {
        // 在这里接收数据，并得到Packet
        recvLen = audioConsumer.readobj(buff);
        sdl2Helper->feedPCM(buff, recvLen);
    }
}
