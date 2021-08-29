#include "demo.h"
#include <QDebug>
demo::demo(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedHeight(164+24);
    this->setFixedWidth(554);

    vecHoursInfo.push_back({21,"sfaf",25});
    vecHoursInfo.push_back({22,"sfaf",24});
    vecHoursInfo.push_back({23,"sfaf",26});
    vecHoursInfo.push_back({00,"sfaf",25});
    vecHoursInfo.push_back({01,"sfaf",27});

    painter=new QPainter();
}

void demo::paintEvent(QPaintEvent *event)
{
    painter->begin(this);
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

    QWidget::paintEvent(event);
}

void demo::setHoursInfo(std::vector<HourInfo> data)
{
    std::vector<HourInfo> temp;

    vecHoursInfo.swap(data);    // 此处替换数据的时候paint可能会出问题
}

void demo::resizeEvent(QResizeEvent *event)
{


    QWidget::resizeEvent(event);
}
