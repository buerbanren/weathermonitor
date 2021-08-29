#ifndef PRECIPITATIONFORECAST_H
#define PRECIPITATIONFORECAST_H

#include <QGridLayout>
#include <QPainter>
#include <QEvent>

#include "../iteminfobase/iteminfobase.h"

struct HourInfo{
    int hour;
    QString strIcoPath;
    int temp;
};

class PrecipitationForecast : public ItemInfoBase
{
public:
    PrecipitationForecast(QWidget *parent);
    virtual void setWeatherInfo(std::string name, std::string value){}
    void paintEvent(QPaintEvent *event);

    void addHourInfo(int hour,QString type,int temp);
    void setHoursInfo(std::vector<HourInfo> data);

    void resizeEvent(QResizeEvent *event);

    bool eventFilter(QObject *object,QEvent *event);

private:
    QGridLayout *gridlayoutPrecipitation=nullptr;
    QWidget *widgetPrecipitationImage=nullptr;

    QPainter *painter=nullptr;

    std::vector<HourInfo> vecHoursInfo;
    QWidget *rainFore=nullptr;

};

#endif // PRECIPITATIONFORECAST_H
