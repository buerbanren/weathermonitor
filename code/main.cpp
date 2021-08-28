#include "weathermonitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WeatherMonitor w;
    //w.showFullScreen();
    w.show();
    return a.exec();
}
