#include "precipitationforecast.h"
#include <QDesktopServices>
#include <QUrl>

PrecipitationForecast::PrecipitationForecast(QWidget *parent)
    :ItemInfoBase(parent)
{
	setTitle(u8"降水预报");

    gridlayoutPrecipitation=new QGridLayout(this);
    gridlayoutPrecipitation->setContentsMargins({0,96,0,39});

    widgetPrecipitationImage=new QWidget(this);
    widgetPrecipitationImage->installEventFilter(this);

    gridlayoutPrecipitation->addWidget(widgetPrecipitationImage);

    this->setLayout(gridlayoutPrecipitation);


    vecHoursInfo.push_back({21,"sfaf",25});
    vecHoursInfo.push_back({22,"sfaf",24});
    vecHoursInfo.push_back({23,"sfaf",26});
    vecHoursInfo.push_back({00,"sfaf",25});
    vecHoursInfo.push_back({01,"sfaf",27});

    painter=new QPainter();
}

void PrecipitationForecast::paintEvent(QPaintEvent *event)
{


    QWidget::paintEvent(event);
}

void PrecipitationForecast::setHoursInfo(std::vector<HourInfo> data)
{
    std::vector<HourInfo> temp;

    vecHoursInfo.swap(data);    // 此处替换数据的时候paint可能会出问题
}

void PrecipitationForecast::resizeEvent(QResizeEvent *event)
{

    gridlayoutPrecipitation->setVerticalSpacing(Common::tranHeight(16));
    gridlayoutPrecipitation->setContentsMargins({ Common::tranWidth(0),
        Common::tranHeight(96),
        Common::tranWidth(0),
        Common::tranHeight(39) });

    QWidget::resizeEvent(event);
}

bool PrecipitationForecast::eventFilter(QObject *object, QEvent *event)
{
    if(widgetPrecipitationImage == static_cast<QWidget*>(object) && QEvent::Paint == event->type())
    {
        painter->begin(widgetPrecipitationImage);
        painter->save();

        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform,true);

        painter->setPen(QColor(0xff,0xff,0xff));
        int index=0;
        foreach(auto it, vecHoursInfo)
        {
            painter->setFont(QFont("Microsoft Yahe",24));
            painter->drawText(QRect{9 + 114 *index, 0, 96, 28}, Qt::AlignHCenter, QString("%1:00").arg(it.hour));

            QImage ico(u8"G:/软件设计稿/和风天气图标/WeatherIcon/weather-icon-S2/256/403.png","png");
            painter->drawImage(QRect{114 * index, 33, 104,104},ico,ico.rect());

            painter->setFont(QFont("Microsoft Yahe",26));
            painter->drawText(QRect{9 + 114 * index, 144, 96, 30},Qt::AlignHCenter, QString(u8"%1℃").arg(it.temp));
            index++;
        }

        painter->restore();
        painter->end();
        return widgetPrecipitationImage->eventFilter(object, event);
    }
    return false;
}
