#include "weathermonitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer timer;
    timer.setInterval(3600000);
    WeatherMonitor w;
    w.showFullScreen();
    w.show();

    timer.connect(&timer,&QTimer::timeout,&w,&WeatherMonitor::startNetworkConfig);

    timer.start();

    return a.exec();
}
