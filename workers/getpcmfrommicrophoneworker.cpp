#include "getpcmfrommicrophoneworker.h"
#include "ndn_ffmpeg_rtc/helper/EasyMicroPhone.h"
#include "ndn_ffmpeg_rtc/ndn_rtp/ndn_rtpp.h"

GetPCMFromMicrophoneWorker::GetPCMFromMicrophoneWorker(QObject *parent, const QString& prefix, const QString& host, int port, int index)
    : QObject(parent), prefix(prefix), host(host), port(port), index(index)
{

}

void GetPCMFromMicrophoneWorker::beginCapturePCMFrameFromMicrophone()
{
    ndn_rtpp audioProducer(this->prefix.toStdString() + "/audio", this->host.toStdString(), this->port);
    EasyMicroPhone easyMicroPhone;
    easyMicroPhone.openMicrophone()
            ->prepare()
            ->begin([=, &audioProducer](AVFrame *frame){
        audioProducer.sendobj(reinterpret_cast<const char *>(frame->data[0]), frame->pkt_size);
        return false;
    });
}
