#ifndef GETVIDEOSTREAMFROMREMOTENDN_H
#define GETVIDEOSTREAMFROMREMOTENDN_H

#include <QObject>
#include <QImage>

class GetVideoStreamFromRemoteNDN : public QObject
{
    Q_OBJECT
public:
    explicit GetVideoStreamFromRemoteNDN(QObject *parent = 0, const QString& prefix = "/producer", const QString& host = "", int port = 6363, int index = 0);

private:
    QString host;
    QString prefix;
    int port;
    int index;
signals:
    void getOneFrame(QImage image, int index);
public slots:
    /**
     * 用NDN传输模块从其他主机拉取视频流信息,并对拉取的视频流进行解压,然后emit一个个QImage
     * @brief beginPullFromRemoteNDN
     */
    void beginPullFromRemoteNDN();
};

#endif // GETVIDEOSTREAMFROMREMOTENDN_H
