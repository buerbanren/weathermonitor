QT += core gui widgets

TEMPLATE = lib
DEFINES += PLATFORM_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/cefwidget/qcefwidget.cpp \
    src/cefwidget/simple_app.cc \
    src/cefwidget/simple_handler.cc \
    src/platform.cpp

HEADERS += \
    src/cefwidget/qcefwidget.h \
    src/cefwidget/simple_app.h \
    src/cefwidget/simple_handler.h \
    include/platform_global.h \
    include/platform.h

INCLUDEPATH += ../extend/libcef
CONFIG(Debug)
{
    LIBS += -L../extend/libcef/lib/debug -llibcef -llibcef_dll_wrapper
}
CONFIG(Release)
{
    LIBS = -L../extend/libcef/lib/release -llibcef -llibcef_dll_wrapper
}

CONFIG(Debug){
MOC_DIR = temp/debug/moc
OBJECTS_DIR = temp/debug/obj
RCC_DIR = temp/debug/rc
UI_DIR = temp/debug/qui
DESTDIR = ../build/debug
}

CONFIG(Release){
MOC_DIR = temp/release/moc
OBJECTS_DIR = temp/release/obj
RCC_DIR = temp/release/
UI_DIR = temp/release/qui
DESTDIR = ../build/release
}
