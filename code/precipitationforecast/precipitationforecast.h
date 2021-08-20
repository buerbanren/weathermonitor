#ifndef PRECIPITATIONFORECAST_H
#define PRECIPITATIONFORECAST_H

#include <QVBoxLayout>
#include <QWebChannel>

#include "../iteminfobase/iteminfobase.h"

class PrecipitationForecast : public ItemInfoBase
{
public:
    PrecipitationForecast(QWidget *parent);


private:
    QVBoxLayout *vlayoutPrecipitation=nullptr;
    QWidget *widgetPrecipitationImage=nullptr;
    QWebChannel *webchannelMap=nullptr;

};

#endif // PRECIPITATIONFORECAST_H
