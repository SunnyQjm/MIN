#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#include <string>
using namespace std;
class GlobalConfig
{
public:
    GlobalConfig();

public:
    static string host;             // 要连接的路由器的IP地址
    static int port;                // 要连接的路由器的NFD端口，默认为6363
    static string contentPrefix;    // 内容发布前缀
};

#endif // GLOBALCONFIG_H
