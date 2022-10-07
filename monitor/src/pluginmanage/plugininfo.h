#ifndef PLUGININFO_H
#define PLUGININFO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>

#include "../../../pluginprecipitationradar/src/interface.h"

class PluginInfo : public QWidget
{
    Q_OBJECT
public:
    explicit PluginInfo(TestInterface *testInterface, QWidget *parent = nullptr);

    void setBaseInfo(QImage img, QString name, QString version, QString author, QString desc);

    void setExtraInfo(QString detail, QString modifiedLog, std::map<QString, QString> more = {});


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
        QVBoxLayout *vlayout_infocontent=nullptr;
        QHBoxLayout *hlayout_infoBase = nullptr;


    QLabel *lab_icoPlugin=nullptr;
    QVBoxLayout *layout_baseText=nullptr;

    QLabel *lab_pluginName = new QLabel(frame_infocontent);
    QLabel *lab_pluginAuthor = new QLabel(frame_infocontent);
    QLabel *lab_pluginDescBase = new QLabel(frame_infocontent);

    QTabWidget *m_pTableInfoDesc=nullptr;


};

#endif // PLUGININFO_H
