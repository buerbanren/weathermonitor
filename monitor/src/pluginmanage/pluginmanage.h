#ifndef PLUGINMANAGE_H
#define PLUGINMANAGE_H

#include <QFrame>
#include <QLabel>
#include <QLibrary>
#include <QMessageBox>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QSpacerItem>

#include "plugininfo.h"
#include "../../../pluginprecipitationradar/src/interface.h"

// 插件配置保存信息
struct PluginConfiguration{
    char name[24];  //名称
    char version[8];    // 版本
    int installed;  // 是否已经安装，0：未安装；1：已安装
};

enum PluginMangePage{
    PLUGIN_ALL=0,
    PLUGIN_SINGLE
};

class PluginManage : public QFrame
{
    Q_OBJECT
public:
    explicit PluginManage(QWidget *parent = nullptr);

    ~PluginManage();

    // 界面布局
    void initUILayout(QWidget *parent);

    // 自动加载插件dll,此函数在关联addPluginPage信号后，进行调用
    void loadPluginDLL();
    // 加载指定插件dll
    bool loadPluginDLL(std::string name, bool isnew=false);

    // 手动选择加载
    void addExtraLibrary();

private:
    std::vector<QPushButton*> vec_pluginBt;
    std::map<std::string,PluginConfiguration> map_pluginConfig; // 插件配置信息

    std::vector<QLibrary*> vet_loadlibrary;
    std::vector<CPluginInterface*> vet_interface;

signals:
    void addPluginPage(QWidget * const widgetplugin);

private:
    // 界面布局
    QVBoxLayout *p_vlayout=nullptr;
        QHBoxLayout *p_hlayoutTop=nullptr;
		QWidget *p_frameTop=nullptr;
            QLabel *p_labPluginTitle=nullptr;
            QSpacerItem *p_hSpacerTop=nullptr;
            QPushButton *p_btClose=nullptr;

    //所有插件页面
    QWidget *p_pluginOperation=nullptr;
    QGridLayout *p_gridLayoutPlugin=nullptr;
        QPushButton *p_btPluginManual=nullptr;
        QSpacerItem *p_hSpacer=nullptr;
        QSpacerItem *p_vSpacer=nullptr;

    QWidget *testWidget=nullptr;

    // 单个插件信息界面
    PluginInfo *p_pluginInfoUI=nullptr;

//////////////////////////////////////////////////////////////////////////////////////

    /*
     * 描述：界面事件继承，实现拖动
     *
     * */
public:
    bool close();
    void changePluginManagePage(PluginMangePage type=PluginMangePage::PLUGIN_ALL);
    void setTitle(std::string title);

protected:
    virtual bool event(QEvent *event);


private:
    QPoint posCursor;
    bool pressed=false;
    std::map<PluginMangePage,QWidget *> map_plugintype;
    std::map<PluginMangePage,std::string> map_plugintitle={
        std::pair<PluginMangePage,std::string>(PLUGIN_ALL,"插件管理"),
        std::pair<PluginMangePage,std::string>(PLUGIN_SINGLE,"插件详情")
    };

    /*
     * 插件配置写入
     * 20210921 插件配置写入，包含文件名，后期需要调整为dll文件md5结果匹配
     *
     * */
public:
    // 刷新配置文件
    bool reflushPluginConfiguration(const std::map<std::string,PluginConfiguration> _map_pluginConfig);
    // 写入配置文件
    bool writePluginConfiguration(PluginConfiguration pluginconfig, bool clean=false);

private:


};

#endif // PLUGINMANAGE_H
