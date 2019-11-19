#include "getframefromcameraworker.h"
#include <ndn_ffmpeg_rtc/helper/EasyCamera.h>
#include <QImage>
#include <ndn_ffmpeg_rtc/ndn_rtp/ndn_rtpp.h>
#include <iostream>
#include <ndn_ffmpeg_rtc/helper/EasyVideoEncoder.h>

using namespace std;
GetFrameFromCameraWorker::GetFrameFromCameraWorker(QObject *parent, const QString& prefix, const QString& host, int port, int index)
    : QObject(parent), prefix(prefix), host(host), port(port), index(index)
{

}

GetFrameFromCameraWorker::~GetFrameFromCameraWorker()
{

}

void GetFrameFromCameraWorker::beginCaptureFrameFromCamera()
{
    EasyCamera easyCamera;
    easyCamera.openCamera()
        ->prepare();
    auto context = easyCamera.getCodecCtx();
    ndn_rtpp producer(this->prefix.toStdString() + "/video", this->host.toStdString(), this->port);
    EasyVideoEncoder easyEncoder(AV_CODEC_ID_H264);

    CodecContextParam param{};
    param.bit_rate = 400000;
    param.width = context->width;
    param.height = context->height;
    param.time_base.num = 1;
    param.time_base.den = 25;
    param.gop_size = 10;
    param.max_b_frames = 1;
    param.pix_fmt = AV_PIX_FMT_YUV420P;

    easyEncoder.initCodecParam(param)
            ->prepareEncode();
    easyCamera.begin([=, &producer, &easyEncoder](AVFrame *pFrameYUV){
        easyEncoder.encode(pFrameYUV, [=, &producer](AVPacket *pkt){
            producer.sendobj((const char *) (pkt->data), pkt->size);
        });
        return false;
    }, [=](AVFrame *pFrameRgb){
        // 通过FFmpeg不抓到视频帧，并转换为argb32
        QImage tmpImg(pFrameRgb->data[0], context->width, context->height, QImage::Format_RGB32);
        // 图像数据拷贝一份
        QImage image = tmpImg.copy();

        //将QImage发送出去
        emit getOneFrame(image, index);
        return false;
    });
}
