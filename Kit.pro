QT       += core gui multimedia
LIBS += -lpthread libwsock32 libws2_32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    compare.cpp \
    main.cpp \
    mylabel.cpp \
    mythread.cpp \
    one.cpp \
    socket.cpp \
    two.cpp \
    utils.cpp \
    widget.cpp

HEADERS += \
    Struct.h \
    compare.h \
    mylabel.h \
    mythread.h \
    one.h \
    socket.h \
    two.h \
    utils.h \
    widget.h

FORMS += \
    one.ui \
    two.ui \
    widget.ui

TRANSLATIONS += \
    Kit_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MP3.qrc \
    character.qrc \
    res.qrc
