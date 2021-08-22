#ifndef ROOMENVIRONMENTMONITOR_H
#define ROOMENVIRONMENTMONITOR_H

#include <QWidget>
#include <QGridLayout>

#include "simpleinfo/simpleweatherinfo.h"
#include "topinfo/topinfo.h"
#include "dialplate/dialplate.h"
#include "weatherinfotoday\weatherinfotoday.h"
#include "precipitationforecast\precipitationforecast.h"

class RoomEnvironmentMonitor : public QWidget
{
    Q_OBJECT

public:
    RoomEnvironmentMonitor(QWidget *parent = nullptr);
    ~RoomEnvironmentMonitor();

protected:
    void resizeEvent(QResizeEvent *event);
    void resolveResponse();

private:
    void initialControl();

private:
    QGridLayout *gridlayoutMain=nullptr;
    TopInfo *topinfo=nullptr;
    SimpleWeatherInfo *simpleinfo=nullptr;
    QSpacerItem *spacerItemTB=nullptr;

    ItemInfoBase *infoToday=nullptr;
	ItemInfoBase *preipitationForececast = nullptr;

protected:
    void initNetworkConfig();


private:
    QNetworkAccessManager *pNetManager=nullptr;
    QNetworkRequest *pNetRequest=nullptr;
    QNetworkReply *pNetReply=nullptr;

    QByteArray jsdata;

    // json文档和对象
    QJsonDocument jsdoc;
    QJsonObject jsobj;



};
#endif // ROOMENVIRONMENTMONITOR_H
