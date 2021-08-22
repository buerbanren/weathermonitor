#ifndef PRECIPITATIONFORECAST_H
#define PRECIPITATIONFORECAST_H

#include <QVBoxLayout>
#include <QWebChannel>

#include "../iteminfobase/iteminfobase.h"

class PrecipitationForecast : public ItemInfoBase
{
public:
    PrecipitationForecast(QWidget *parent);
    virtual void setWeatherInfo(std::string name, std::string value){}


private:
    QVBoxLayout *vlayoutPrecipitation=nullptr;
    QWidget *widgetPrecipitationImage=nullptr;
    QWebChannel *webchannelMap=nullptr;

};

#endif // PRECIPITATIONFORECAST_H
