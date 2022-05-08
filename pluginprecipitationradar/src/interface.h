#ifndef INTERFACE_H
#define INTERFACE_H

#include "pluginprecipitationradar_global.h"

#include <QWidget>

struct stuPluginInfo
{
    QImage ico;
    std::string name;
    std::string version;
    std::string copyright;
    std::string lastTime;
    std::string description;
};

class TestInterface: public QObject
{
public:
    virtual ~TestInterface(){}
    // 获取插件界面
    virtual QWidget *getPluginWidget()=0;

    // 获取插件应用图标
    virtual QImage getPluginIcon()=0;

    // 获取插件信息
    virtual void getPluginInfo(stuPluginInfo &info)=0;

};

#endif // INTERFACE_H
