#ifndef TEST_H
#define TEST_H

#include "test_global.h"

#include <QWidget>

class TestInterface
{
public:
    // 获取插件界面
    virtual QWidget *getPluginWidget()=0;

    // 获取插件应用图标
    virtual QImage getPluginIcon()=0;

};

#endif // TEST_H
