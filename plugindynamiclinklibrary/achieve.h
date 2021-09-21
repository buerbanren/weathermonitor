#ifndef ACHIEVE_H
#define ACHIEVE_H

#include "interface.h"

// 动态库导出接口
extern "C" TestInterface* TEST_EXPORT getInstall();

class AchieveClass: public TestInterface
{
public:
    AchieveClass();

    // 获取插件界面
    virtual QWidget *getPluginWidget();

    // 获取插件应用图标
    virtual QImage getPluginIcon();

    ~AchieveClass();

private:
    QWidget *widget=nullptr;

};

#endif // ACHIEVE_H
