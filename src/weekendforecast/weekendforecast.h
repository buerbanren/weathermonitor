#ifndef WEEKENDFORECAST_H
#define WEEKENDFORECAST_H

#include <QGridLayout>
#include <QPainter>
#include <QEvent>
#include <QTimer>
#include <string>

#include "../common/comdefine.h"
#include "../iteminfobase/iteminfobase.h"

struct DayInfo{
    string day;
    string strIcoPath;
    string windDirection;
    string windRank;
    int tempMin;
    int tempMax;
};

class WeekendForecast : public ItemInfoBase
{
public:
    WeekendForecast(QWidget *parent);
    ~WeekendForecast();
    virtual void setWeatherInfo(std::string name, std::string value){}
    void paintEvent(QPaintEvent *event);

    void addDayInfo(int hour,QString type,int temp);
    void setDaysInfo(std::vector<DayInfo> data);

    void resizeEvent(QResizeEvent *event);

    bool eventFilter(QObject *object,QEvent *event);

    void timingMove();

private:
    QGridLayout *gridlayoutPrecipitation=nullptr;
    QWidget *widgetPrecipitationImage=nullptr;

    QPainter *painter=nullptr;

    std::vector<DayInfo> vecDaysInfo;
    QWidget *rainFore=nullptr;


    QTimer timerDay;
    int startY=0;

};

#endif // WEEKENDFORECAST_H
