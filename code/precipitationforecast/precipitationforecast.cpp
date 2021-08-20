#include "precipitationforecast.h"
#include <QDesktopServices>
#include <QUrl>

PrecipitationForecast::PrecipitationForecast(QWidget *parent)
    :ItemInfoBase(parent)
{
	setTitle(u8"降水预报");

    vlayoutPrecipitation=new QVBoxLayout(this);
    vlayoutPrecipitation->setContentsMargins({30,96,40,30});

    widgetPrecipitationImage=new QWidget(this);

    vlayoutPrecipitation->addWidget(widgetPrecipitationImage);

    this->setLayout(vlayoutPrecipitation);
}
