#include "weekendforecast.h"
#include <QDesktopServices>
#include <QUrl>

WeekendForecast::WeekendForecast(QWidget *parent)
    :ItemInfoBase(parent)
{
    setTitle(u8"7天预报");

    gridlayoutPrecipitation=new QGridLayout(this);

    widgetPrecipitationImage=new QWidget(this);
    widgetPrecipitationImage->setStyleSheet("border:0px;");
    widgetPrecipitationImage->installEventFilter(this);

    gridlayoutPrecipitation->addWidget(widgetPrecipitationImage);

    this->setLayout(gridlayoutPrecipitation);
    this->setStyleSheet("background:transparent;");

    vecDaysInfo.push_back({ "09-12",u8"多云",u8"北风",u8"3级",23,25 });
    vecDaysInfo.push_back({ "09-13",u8"晴",u8"北风",u8"3级",20,24 });
    vecDaysInfo.push_back({ "09-14",u8"阵雨",u8"北风",u8"3级",03,23 });
    vecDaysInfo.push_back({ "09-15",u8"阵雨",u8"北风",u8"3级",20,22 });
    vecDaysInfo.push_back({ "09-16",u8"阵雨",u8"北风",u8"3级",20,22 });
    vecDaysInfo.push_back({ "09-17",u8"阵雨",u8"北风",u8"3级",18,21 });
    vecDaysInfo.push_back({ "09-18",u8"阵雨",u8"北风",u8"3级",18,29 });

    painter=new QPainter();

    // 开启定时器，以两秒为周期移动
    timerDay.setInterval(3000);
    timerDay.start();

    connect(&timerDay, &QTimer::timeout,this, &WeekendForecast::timingMove);

}

WeekendForecast::~WeekendForecast()
{
    timerDay.stop();
}

void WeekendForecast::paintEvent(QPaintEvent *event)
{


    ItemInfoBase::paintEvent(event);
}

void WeekendForecast::setDaysInfo(std::vector<DayInfo> data)
{
    std::vector<DayInfo> temp;

    vecDaysInfo.swap(data);    // 此处替换数据的时候paint可能会出问题
}

void WeekendForecast::resizeEvent(QResizeEvent *event)
{

    gridlayoutPrecipitation->setVerticalSpacing(Common::tranHeight(16));
    gridlayoutPrecipitation->setContentsMargins({ Common::tranWidth(0),
        Common::tranHeight(86),
        Common::tranWidth(0),
        Common::tranHeight(11) });

    ItemInfoBase::resizeEvent(event);
}

bool WeekendForecast::eventFilter(QObject *object, QEvent *event)
{
    if(widgetPrecipitationImage == static_cast<QWidget*>(object) && QEvent::Paint == event->type())
    {
        painter->begin(widgetPrecipitationImage);
        painter->save();

        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform,true);

        painter->setPen(QColor(0xff,0xff,0xff));
		QString _temp;
        int index=0;
        foreach(auto it, vecDaysInfo)
        {
            // 预报日期
            painter->setFont(QFont("Microsoft Yahei", Common::tranHeight(18), 1));
            painter->drawText(QRect{ Common::tranWidth(32), Common::tranHeight(startY + 0 + index * 52), Common::tranWidth(72), Common::tranHeight(52) }, Qt::AlignCenter, it.day.data());

			// 天气图标
            QImage ico(it.strIcoPath.data(),"png");
            painter->drawImage(QRect{ Common::tranWidth(169), Common::tranHeight(startY + 0 + index * 52), Common::tranWidth(57),Common::tranHeight(52) }, ico, ico.rect());

			// 风力
			painter->setFont(QFont("Microsoft Yahei", Common::tranHeight(18)));
            _temp = QString(u8"%1 %2").arg(it.windDirection.data()).arg(it.windRank.data());
            painter->drawText(QRect{ Common::tranWidth(270), Common::tranHeight(startY + 0 + index * 52), Common::tranWidth(96),Common::tranHeight(52) }, Qt::AlignCenter, _temp);

			// 最高最低温度
            painter->setFont(QFont("Microsoft Yahei",Common::tranHeight(18)));
			_temp = QString(u8"%1 / %2℃").arg(it.tempMin).arg(it.tempMax);
            painter->drawText(QRect{ Common::tranWidth(408), Common::tranHeight(startY + 0 + index * 52), Common::tranWidth(101), Common::tranHeight(52) }, Qt::AlignHCenter, _temp);
            index++;
        }

        painter->restore();
        painter->end();
        return widgetPrecipitationImage->eventFilter(object, event);
    }
    return false;
}

void WeekendForecast::timingMove()
{
    // 3s周期响应
    if(3000==timerDay.interval())
    {
        timerDay.stop();
        timerDay.setInterval(80);
        timerDay.start();
    }
    else if(80 == timerDay.interval())
    {
        startY-=6;
        this->update();
        if(abs(startY) % 54 == 0)
        {
            timerDay.stop();
            timerDay.setInterval(3000);
            timerDay.start();
        }
        if(abs(startY) / 54 == 4)
        {
            startY=0;
        }
    }
}
