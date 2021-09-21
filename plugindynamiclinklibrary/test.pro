QT += widgets gui

TEMPLATE = lib
DEFINES += TEST_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achieve.cpp

HEADERS += \
    achieve.h \
    interface.h \
    test_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}

CONFIG(Debug){
MOC_DIR = temp/debug/moc
OBJECTS_DIR = temp/debug/obj
RCC_DIR = temp/debug/rc
UI_DIR = temp/debug/qui
DESTDIR = ../build/debug
}

CONFIG(Release){
MOC_DIR = temp/debug/moc
OBJECTS_DIR = temp/debug/obj
RCC_DIR = temp/debug/
UI_DIR = temp/debug/qui
DESTDIR = ../build/debug
}

!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    test.qrc
