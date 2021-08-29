#include "precipitationforecast.h"
#include <QDesktopServices>
#include <QUrl>

PrecipitationForecast::PrecipitationForecast(QWidget *parent)
    :ItemInfoBase(parent)
{
	setTitle(u8"降水预报");

    gridlayoutPrecipitation=new QGridLayout(this);

    widgetPrecipitationImage=new QWidget(this);
    widgetPrecipitationImage->setStyleSheet("border:0px;");
    widgetPrecipitationImage->installEventFilter(this);

    gridlayoutPrecipitation->addWidget(widgetPrecipitationImage);

    this->setLayout(gridlayoutPrecipitation);
    this->setStyleSheet("background:transparent;");

    vecHoursInfo.push_back({21,"sfaf",25});
    vecHoursInfo.push_back({22,"sfaf",24});
    vecHoursInfo.push_back({23,"sfaf",23});
    vecHoursInfo.push_back({00,"sfaf",22});
    vecHoursInfo.push_back({01,"sfaf",22});
    vecHoursInfo.push_back({02,"sfaf",21});
    vecHoursInfo.push_back({03,"sfaf",19});

    painter=new QPainter();

    // 开启定时器，以两秒为周期移动
    timer.setInterval(3000);
    timer.start();

    connect(&timer, &QTimer::timeout,this, &PrecipitationForecast::timingMove);

}

PrecipitationForecast::~PrecipitationForecast()
{
    timer.stop();

}

void PrecipitationForecast::paintEvent(QPaintEvent *event)
{


    ItemInfoBase::paintEvent(event);
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

    ItemInfoBase::resizeEvent(event);
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
            painter->setFont(QFont("Microsoft Yahei",Common::tranHeight(18)));
            painter->drawText(QRect{Common::tranWidth(startX + 2 + 110 *index), 0, Common::tranWidth(96), Common::tranHeight(28)}, Qt::AlignHCenter, QString("%1:00").arg(it.hour));

            QImage ico(u8"G:/软件设计稿/和风天气图标/WeatherIcon/weather-icon-S2/256/403.png","png");
            painter->drawImage(QRect{Common::tranWidth(startX + 110 * index), Common::tranHeight(33), Common::tranWidth(104),Common::tranHeight(104)},ico,ico.rect());

            painter->setFont(QFont("Microsoft Yahei",Common::tranHeight(18)));
            painter->drawText(QRect{Common::tranWidth(startX + 2 + 110 * index), Common::tranHeight(140), Common::tranWidth(96), Common::tranHeight(30)},Qt::AlignHCenter, QString(u8"%1℃").arg(it.temp));
            index++;
        }

        painter->restore();
        painter->end();
        return widgetPrecipitationImage->eventFilter(object, event);
    }
    return false;
}

void PrecipitationForecast::timingMove()
{
    // 3s周期响应
    if(3000==timer.interval())
    {
        timer.stop();
        timer.setInterval(40);
        timer.start();
    }
    else if(40 == timer.interval())
    {
        startX-=5;
        this->update();
        if(abs(startX) % 110 == 0)
        {
            timer.stop();
            timer.setInterval(3000);
            timer.start();
        }
        if(abs(startX) / 110 == 3)
        {
            startX=0;
        }
    }
}
