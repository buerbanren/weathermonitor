#include "uimanage.h"

UIManage::UIManage(QObject *parent) : QObject(parent)
{
    timer.setInterval(3600000);
    w=new WeatherMonitor(nullptr);
    w->showFullScreen();

    timer.connect(&timer, &QTimer::timeout, w, &WeatherMonitor::startNetworkConfig);

    monitormenu=new MonitorMenu(w);
    monitormenu->show();

    //timer.start();
    pluginManage=new PluginManage(w);
    pluginManage->move((w->width() - pluginManage->width()) / 2, (w->height() - pluginManage->height()) / 2);
    pluginManage->hide();

    connect(monitormenu,&MonitorMenu::menuChanged,[=](std::string name)
    {
        if(name.compare("plugin")==0)
        {
            pluginManage->show();
            return;
        }
    });
}

void UIManage::show()
{
    w->show();
}

void UIManage::hide()
{
    w->hide();
}
