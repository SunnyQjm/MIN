#-------------------------------------------------
#
# Project created by QtCreator 2019-11-11T16:23:52
#
#-------------------------------------------------

QT       += core gui sql multimedia
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = min
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS_RELEASE += -g

QMAKE_CFLAGS_RELEASE += -g

QMAKE_LFLAGS_RELEASE = -pthread -W



# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lSDL2 \
    -lavcodec \
    -lavformat \
    -lswscale \
    -lavdevice \
    -lswresample \
    -lavutil \
    -lpthread \
    -lpcap \
    -lndn-cxx\
    -lboost_system

# helper 相关
SOURCES += $$PWD/ndn_ffmpeg_rtc/helper/*.cpp \
    logindialog.cpp \
    workers/getframefromcameraworker.cpp \
#    ndnrtcwindow.cpp \
    ndnrtcdialog.cpp \
    workers/getvideostreamfromremotendn.cpp \
    globalconfig.cpp \
    workers/getpcmfrommicrophoneworker.cpp \
    workers/pcmplayerworker.cpp \
    helper/dbhelper.cpp

#    widgets/sdl2render.cpp \
#    sdl2render.cpp
HEADERS += $$PWD/ndn_ffmpeg_rtc/helper/*.h \
    logindialog.h \
    workers/getframefromcameraworker.h \
#    ndnrtcwindow.h \
    ndnrtcdialog.h \
    workers/getvideostreamfromremotendn.h \
    globalconfig.h \
    workers/getpcmfrommicrophoneworker.h \
    workers/pcmplayerworker.h \
    helper/dbhelper.h
#    widgets/sdl2render.h\
#    sdl2render.h

# ndn_rtp相关
SOURCES += $$PWD/ndn_ffmpeg_rtc/ndn_rtp/*.cpp
HEADERS += $$PWD/ndn_ffmpeg_rtc/ndn_rtp/*.h

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui \
#    sdl2render.ui \
#    ndnrtcwindow.ui \
    logindialog.ui \
    ndnrtcdialog.ui

#unix:!macx: LIBS += -L$$PWD/helper/lib/ -lffmpeg_helper

#INCLUDEPATH += $$PWD/helper/include
#DEPENDPATH += $$PWD/helper/include

#unix:!macx: PRE_TARGETDEPS += $$PWD/helper/lib/libffmpeg_helper.a

#unix:!macx: LIBS += -L$$PWD/helper/lib/ -lsdl_helper

#INCLUDEPATH += $$PWD/helper/include
#DEPENDPATH += $$PWD/helper/include

#unix:!macx: PRE_TARGETDEPS += $$PWD/helper/lib/libsdl_helper.a

#unix:!macx: LIBS += -L$$PWD/helper/lib/ -lndn_rtp

#INCLUDEPATH += $$PWD/helper/include
#DEPENDPATH += $$PWD/helper/include
