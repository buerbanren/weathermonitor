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

    std::string detail;
    std::string modifiedLog;
    std::map<QString, QString> extraDescript;
};

class CPluginInterface: public QObject
{
public:
    virtual ~CPluginInterface(){}
    // 获取插件界面
    virtual QWidget *getPluginWidget()=0;

    // 获取插件应用图标
    virtual QImage getPluginIcon()=0;

    // 获取插件信息
    virtual void getPluginInfo(stuPluginInfo &info)=0;

};

#endif // INTERFACE_H
