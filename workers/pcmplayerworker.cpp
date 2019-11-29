#include "pcmplayerworker.h"
#include "ndn_ffmpeg_rtc/ndn_rtp/ndn_rtpc.h"

PCMPlayerWorker::PCMPlayerWorker(QObject *parent, const QString& prefix, const QString& host, int port, int index)
    : QObject(parent), prefix(prefix), host(host), port(port), index(index)
{

}

PCMPlayerWorker::~PCMPlayerWorker()
{
    this->audioIO->close();
    this->out->stop();
}

void PCMPlayerWorker::beginPlayerPCM()
{
    ndn_rtpc audioConsumer(this->prefix.toStdString() + "/audio", this->host.toStdString(), this->port);
//    SDL2Helper sdl2Helper1(SDL_INIT_AUDIO);
//    sdl2Helper1.setAudioSpecFreq(48000)
//            ->setAudioSpecFormat(AUDIO_S16SYS)
//            ->setAudioSpecChannels(2)
//            ->setAudioSpecSilence(0)
//            ->setAudioSpecSamples(1024)
//            ->openAudio()
//            ->pauseAudio(0);
    QAudioFormat fmt;
    fmt.setSampleRate(48000);  //设定播放采样频率为44100Hz的音频文件
    fmt.setSampleSize(16);     //设定播放采样格式（采样位数）为16位(bit)的音频文件。QAudioFormat支持的有8/16bit，即将声音振幅化为256/64k个等级
    fmt.setChannelCount(2);    //设定播放声道数目为2通道（立体声）的音频文件。mono(平声道)的声道数目是1，stero(立体声)的声道数目是2
    fmt.setCodec("audio/pcm"); //播放PCM数据（裸流）得设置编码器为"audio/pcm"。"audio/pcm"在所有的平台都支持，也就相当于音频格式的WAV,以线性方式无压缩的记录捕捉到的数据。如想使用其他编码格式 ，可以通过QAudioDeviceInfo::supportedCodecs()来获取当前平台支持的编码格式
    fmt.setByteOrder(QAudioFormat::LittleEndian); //设定字节序，以小端模式播放音频文件
    fmt.setSampleType(QAudioFormat::UnSignedInt); //设定采样类型。根据采样位数来设定。采样位数为8或16位则设置为QAudioFormat::UnSignedInt
    this->out = new QAudioOutput(fmt);    //创建QAudioOutput对象并初始化
    this->audioIO = this->out->start();
    uint32_t recvLen;
    char buff[200000];
    while(true) {
        // 在这里接收数据，并得到Packet
        recvLen = audioConsumer.readobj(buff);
//        sdl2Helper1.feedPCM(buff, recvLen);
        this->audioIO->write(buff, recvLen);
    }
}
