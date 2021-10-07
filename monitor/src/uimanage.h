#ifndef UIMANAGE_H
#define UIMANAGE_H

#include <QObject>
#include "weathermonitor.h"
#include "monitormenu/monitormenu.h"
#include "pluginmanage/pluginmanage.h"
#include "about/aboutdialog.h"

class UIManage : public QObject
{
    Q_OBJECT
public:
    explicit UIManage(QObject *parent = nullptr);

    void show();
    void hide();

signals:
    void exit(int code);

private:

    QTimer timer;
    WeatherMonitor *w=nullptr;
    MonitorMenu *monitormenu=nullptr;
    PluginManage *pluginManage=nullptr;
    AboutDialog *paboutDialog=nullptr;

};

#endif // UIMANAGE_H
