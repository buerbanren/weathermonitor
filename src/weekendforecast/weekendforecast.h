#ifndef WEEKENDFORECAST_H
#define WEEKENDFORECAST_H

#include <QGridLayout>
#include <QPainter>
#include <QEvent>
#include <QTimer>
#include <string>

#include "../iteminfobase/iteminfobase.h"

struct DayInfo{
    int day;
    QString strIcoPath;
    QString windDirection;
    QString windRank;
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

	std::map<int, std::string> mapDays = {
		std::pair<int,std::string>(0,"星期天"),
		std::pair<int,std::string>(1,"星期一"),
		std::pair<int,std::string>(2,"星期二"),
		std::pair<int,std::string>(3,"星期三"),
		std::pair<int,std::string>(4,"星期四"),
		std::pair<int,std::string>(5,"星期五"),
		std::pair<int,std::string>(6,"星期六")
    };

};

#endif // WEEKENDFORECAST_H
