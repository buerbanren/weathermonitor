#include "weathermonitor.h"
#include "pluginmanage/pluginmanage.h"

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

    //timer.start();

    PluginManage pluginManage(&w);
    pluginManage.move((w.width()-pluginManage.width())/2,(w.height()-pluginManage.height())/2);
    pluginManage.show();

    return a.exec();
}
