#ifndef WEATHERMONITOR_H
#define WEATHERMONITOR_H

#include <QWidget>
#include <QGridLayout>
#include <QDateTime>
#include <QString>

#include "simpleinfo/simpleweatherinfo.h"
#include "topinfo/topinfo.h"
#include "dialplate/dialplate.h"
#include "weatherinfotoday/weatherinfotoday.h"
#include "precipitationforecast/precipitationforecast.h"
#include "weekendforecast/weekendforecast.h"

class WeatherMonitor : public QWidget
{
    Q_OBJECT

public:
    WeatherMonitor(QWidget *parent = nullptr);
    ~WeatherMonitor();

protected:
    void resizeEvent(QResizeEvent *event);
    void resolveResponseWeather();
    void resolveResponseWarn();

private:
    void initialControl();

private:
    QGridLayout *gridlayoutMain=nullptr;
    TopInfo *topinfo=nullptr;
    SimpleWeatherInfo *simpleinfo=nullptr;
    QSpacerItem *spacerItemTB=nullptr;

    WeatherInfoToday *infoToday=nullptr;
    PrecipitationForecast *preipitationForececast = nullptr;
    WeekendForecast *weekendForecast=nullptr;

protected:
    void initNetworkConfig();


private:
    QNetworkAccessManager *pNetManager=nullptr;
    QNetworkRequest *pNetRequest=nullptr;
    QNetworkReply *pNetReply=nullptr;
    QByteArray jsdata;

    QNetworkRequest *pNetRequestWarn=nullptr;
    QNetworkReply *pNetReplyWarn=nullptr;
    QByteArray jsdataWarn;


    // json文档和对象
    QJsonDocument jsdoc;
    QJsonObject jsobj;



};
#endif // WEATHERMONITOR_H
