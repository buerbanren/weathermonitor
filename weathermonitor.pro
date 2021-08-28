QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webchannel

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    code/common/comdefine.cpp \
    code/dialplate/dialplate.cpp \
    code/iteminfobase/iteminfobase.cpp \
    code/main.cpp \
    code/precipitationforecast/precipitationforecast.cpp \
    code/topinfo/topinfo.cpp \
    code/simpleinfo/simpleweatherinfo.cpp \
    code/weatherinfotoday/weatherinfotoday.cpp \
    code/dialimage/dialimage.cpp \
    code/weathermonitor.cpp

HEADERS += \
    code/common/comdefine.h \
    code/dialplate/dialplate.h \
    code/iteminfobase/iteminfobase.h \
    code/precipitationforecast/precipitationforecast.h \
    code/topinfo/topinfo.h \
    code/simpleinfo/simpleweatherinfo.h \
    code/weatherinfotoday/weatherinfotoday.h \
    code/dialimage/dialimage.h \
    code/weathermonitor.h

RESOURCES += \
    code/roomenvironmentmonitor.qrc

TARGET = weathermonitor

VERSION = 0.0.1

CONFIG(Debug){
MOC_DIR = temp/debug/moc
OBJECTS_DIR = temp/debug/obj
RCC_DIR = temp/debug/rc
UI_DIR = temp/debug/qui
DESTDIR = output/debug
}

CONFIG(Release){
MOC_DIR = temp/debug/moc
OBJECTS_DIR = temp/debug/obj
RCC_DIR = temp/debug/
UI_DIR = temp/debug/qui
DESTDIR = output/debug
}

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

