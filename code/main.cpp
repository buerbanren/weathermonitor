#include "roomenvironmentmonitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RoomEnvironmentMonitor w;
    //w.showFullScreen();
    w.show();
    return a.exec();
}
