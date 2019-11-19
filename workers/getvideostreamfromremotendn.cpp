#include "getvideostreamfromremotendn.h"
#include <QImage>
#include <ndn_ffmpeg_rtc/ndn_rtp/ndn_rtpc.h>
#include <iostream>
#include <ndn_ffmpeg_rtc/helper/EasyVideoDecoder.h>
#include <ndn_ffmpeg_rtc/helper/FFmpegUtil.h>

using namespace std;
GetVideoStreamFromRemoteNDN::GetVideoStreamFromRemoteNDN(QObject *parent, const QString& prefix, const QString& host, int port, int index)
    : QObject(parent), prefix(prefix), host(host), port(port), index(index)
{

}

void GetVideoStreamFromRemoteNDN::beginPullFromRemoteNDN()
{
    ndn_rtpc videoConsumer(this->prefix.toStdString() + "/video",
                           this->host.toStdString(),
                           this->port);
    EasyVideoDecoder easyDecoder(AV_CODEC_ID_H264);
        easyDecoder.prepareDecode();
    char buff[200000];
    int recvLen;
    int width = 0;
    int height = 0;
    AVFrame *pFrameRGB = nullptr;
    SwsContext* convertContext = nullptr;
    while(true) {
        try {
            recvLen = videoConsumer.readobj(buff);
            cout << "recvLen: " << recvLen << endl;
            AVPacket *pkt = easyDecoder.parse((const uint8_t *) buff, recvLen);
            if (pkt == nullptr) {
                continue;
            }
            int tmpWidth = width;
            int tmpHeight = height;
            easyDecoder.decode(pkt, [=, &tmpWidth, &tmpHeight](AVFrame* pFrame){
                if(tmpWidth != pFrame->width || tmpHeight != pFrame->height) {
                    tmpWidth = pFrame->width;
                    tmpHeight = pFrame->height;
                }
                if(pFrameRGB == nullptr)
                    return;
                sws_scale(convertContext,
                            (uint8_t const * const *) pFrame->data,
                            pFrame->linesize, 0, height, pFrameRGB->data,
                            pFrameRGB->linesize);
                QImage tmpImg(pFrameRGB->data[0], width, height, QImage::Format_RGB32);
                QImage image = tmpImg.copy();
                emit getOneFrame(image, this->index);
            });
            if(tmpWidth != width || tmpHeight != height) {
                width = tmpWidth;
                height = tmpHeight;
                convertContext = sws_getContext(width, height, AV_PIX_FMT_YUV420P, width, height, AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);
                pFrameRGB = EasyFFmpeg::FFmpegUtil::allocAVFrameAndDataBufferWithType(AV_PIX_FMT_RGB32, width, height);
            }
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}
