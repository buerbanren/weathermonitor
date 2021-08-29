QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webchannel

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/common/comdefine.cpp \
    src/dialplate/dialplate.cpp \
    src/iteminfobase/iteminfobase.cpp \
    src/main.cpp \
    src/precipitationforecast/precipitationforecast.cpp \
    src/weekendforecast/weekendforecast.cpp \
    src/topinfo/topinfo.cpp \
    src/simpleinfo/simpleweatherinfo.cpp \
    src/weatherinfotoday/weatherinfotoday.cpp \
    src/dialimage/dialimage.cpp \
    src/weathermonitor.cpp

HEADERS += \
    src/common/comdefine.h \
    src/dialplate/dialplate.h \
    src/iteminfobase/iteminfobase.h \
    src/precipitationforecast/precipitationforecast.h \
    src/weekendforecast/weekendforecast.h \
    src/topinfo/topinfo.h \
    src/simpleinfo/simpleweatherinfo.h \
    src/weatherinfotoday/weatherinfotoday.h \
    src/dialimage/dialimage.h \
    src/weathermonitor.h

RESOURCES += \
    src/roomenvironmentmonitor.qrc

TARGET = weathermonitor

VERSION = 0.0.1

CONFIG(Debug){
MOC_DIR = temp/debug/moc
OBJECTS_DIR = temp/debug/obj
RCC_DIR = temp/debug/rc
UI_DIR = temp/debug/qui
DESTDIR = build/debug
}

CONFIG(Release){
MOC_DIR = temp/debug/moc
OBJECTS_DIR = temp/debug/obj
RCC_DIR = temp/debug/
UI_DIR = temp/debug/qui
DESTDIR = build/debug
}

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

