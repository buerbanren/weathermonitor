#include <QCoreApplication>
#include "uimanage.h"

UIManage::UIManage(QObject *parent) : QObject(parent)
{
    timer.setInterval(3600000);
    w=new WeatherMonitor(nullptr);
    w->showFullScreen();

    timer.connect(&timer, &QTimer::timeout, w, &WeatherMonitor::startNetworkConfig);

    monitormenu=new MonitorMenu(w);
    monitormenu->show();

    // 菜单退出信号
    connect(monitormenu,&MonitorMenu::menuChanged,[=](std::string name)
    {
        if(name.compare("plugin")==0)
        {
            pluginManage->show();
            return;
        }
        else if(name.compare("exit")==0)
        {
            timer.stop();
            emit exit(0);
            return;
        }
        else if(name.compare("about")==0)
        {
            this->paboutDialog->exec();
            return;
        }
    });

    timer.start();
    pluginManage=new PluginManage(w);
    pluginManage->move((w->width() - pluginManage->width()) / 2, (w->height() - pluginManage->height()) / 2);
    pluginManage->hide();
    // 插件界面加载信号，此关联必须位于加载插件之前
    connect(pluginManage,&PluginManage::addPluginPage,[=](QWidget * const widget)
    {
        w->addPluginPage(widget);
    });
    pluginManage->loadPluginDLL();

    paboutDialog=new AboutDialog(w);

}

void UIManage::show()
{
    w->show();
}

void UIManage::hide()
{
    w->hide();
}
