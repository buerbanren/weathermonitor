#ifndef PLUGININFO_H
#define PLUGININFO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "../../../plugindynamiclinklibrary/interface.h"

class PluginInfo : public QWidget
{
    Q_OBJECT
public:
    explicit PluginInfo(TestInterface *testInterface, QWidget *parent = nullptr);

Q_SIGNALS:
    void returnPluginPage();

private:
    void init();


private:
    QVBoxLayout *vlayout_info=nullptr;
        // 顶部返回按键
        QWidget *frame_infotop=nullptr;
        QHBoxLayout *hlayout_infotop=nullptr;
        QPushButton *btReturn=nullptr;
        QSpacerItem *hspacer_info=nullptr;
        // 插件信息窗口
        QWidget *frame_infocontent=nullptr;
        QHBoxLayout *hlayout_infocontent=nullptr;

};

#endif // PLUGININFO_H
