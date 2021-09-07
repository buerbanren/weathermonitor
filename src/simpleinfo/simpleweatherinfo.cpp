#include "simpleweatherinfo.h"
#include <QFile>
#include <QPainter>

SimpleWeatherInfo::SimpleWeatherInfo(QWidget *parent) : QWidget(parent)
{
    initialControl();

    // 注册预警label的事件过滤器
    labelWarning->installEventFilter(this);

    timer.setInterval(10000);
    timer.start();

    connect(&timer, &QTimer::timeout,this, &SimpleWeatherInfo::timingMove);

}

SimpleWeatherInfo::~SimpleWeatherInfo()
{

}

void SimpleWeatherInfo::resizeEvent(QResizeEvent *event)
{
    this->setStyleSheet(this->strStyle.arg(Common::tranHeight(28)).arg(Common::tranHeight(72))
                        .arg(Common::tranHeight(48)).arg(Common::tranHeight(32)));

    labelWeatherImg->setFixedHeight(Common::tranWidth(214));

    labelWarning->setFixedWidth(Common::tranWidth(560));
    //labelAirQuality->setIconSize({Common::tranWidth(56),Common::tranHeight(56)});

    hlayoutDial->setContentsMargins({Common::tranWidth(83),0,0,0});
    hlayoutDial->setSpacing(Common::tranWidth(83));

    dialTemp->setFixedSize(Common::tranWidth(320),Common::tranHeight(320));
    dialHumidity->setFixedSize(Common::tranWidth(320),Common::tranHeight(320));

    QWidget::resizeEvent(event);
}

bool SimpleWeatherInfo::eventFilter(QObject *object, QEvent *event)
{
    if(labelWarning == object)
    {
        if(!labelWarning->text().isEmpty())
        {
            strWarn="";
            strWarn=labelWarning->text();
            labelWarning->clear();
        }

        QPainter painter;
        painter.begin(labelWarning);
        painter.save();
        //28px;

        QRect _rect=labelWarning->rect();
        _rect.setX(startX);
        painter.setPen(QColor(0xff,0x00,0x00));
        painter.setFont(QFont("Microsoft Yahei",Common::tranHeight(24)));

        painter.drawText(_rect,Qt::AlignLeft | Qt::AlignVCenter,strWarn);

        painter.restore();
        painter.end();
    }

    return QWidget::eventFilter(object,event);
}

void SimpleWeatherInfo::initialControl()
{
    hlayoutSimpleInfo=new QHBoxLayout(this);
    hlayoutSimpleInfo->setContentsMargins({0,0,0,0});
    this->setLayout(hlayoutSimpleInfo);

    // 天气图标
    labelWeatherImg=new QLabel(this);
    labelWeatherImg->setStyleSheet("image:url(:/weathericons/resource/weathericons/302.png);");
    gridlayoutDescription=new QGridLayout(this);
    gridlayoutDescription->setContentsMargins({0,0,0,0});

    hlayoutSimpleInfo->addWidget(labelWeatherImg);
    //hlayoutSimpleInfo->addSpacing(50);

    labelWarning=new QLabel(this);
    labelWarning->setObjectName("labelWarning");
    labelWarning->setText(u8"青岛市气象台2021年8月32日1");
    gridlayoutDescription->addWidget(labelWarning,0,0,1,2);

    labelTemperature=new QLabel(this);
    labelTemperature->setObjectName("labTemperature");
    labelTemperature->setAlignment(Qt::AlignCenter);
    labelTemperature->setText(u8"00℃");
    gridlayoutDescription->addWidget(labelTemperature,1,0);

    labelAirQuality=new QLabel(this);
    labelAirQuality->setObjectName("labelAirQuality");
    //labelAirQuality->setIcon(QIcon(":/qss/resource/qss/airquality.png"));
    //labelAirQuality->setCheckable(false);
    labelAirQuality->setText(u8"空气质量");
    labelAirQuality->setAlignment(Qt::AlignCenter);
    gridlayoutDescription->addWidget(labelAirQuality,1,1);

    labelRainStatus=new QLabel(this);
    labelRainStatus->setObjectName("labelRainStatus");
    labelRainStatus->setText(u8"");
    labelRainStatus->setAlignment(Qt::AlignCenter);
    gridlayoutDescription->addWidget(labelRainStatus,2,0);

    labelTempMaxMin=new QLabel(this);
    labelTempMaxMin->setObjectName("labelTempMaxMin");
    labelTempMaxMin->setText(u8"00 ℃ / 00 ℃");
    labelTempMaxMin->setAlignment(Qt::AlignCenter);
    gridlayoutDescription->addWidget(labelTempMaxMin,2,1);

    QFile cssfile(":/qss/resource/qss/simpleweatherinfo.css");
    if(cssfile.open(QIODevice::ReadOnly))
    {
        this->strStyle=cssfile.readAll();
        this->setStyleSheet(this->strStyle.arg(Common::tranHeight(28)).arg(Common::tranHeight(72))
                            .arg(Common::tranWidth(48)).arg(Common::tranHeight(32)));
    }

    hlayoutSimpleInfo->addLayout(gridlayoutDescription);
    //hlayoutSimpleInfo->addSpacing(120);

    hlayoutDial=new QHBoxLayout(this);
    hlayoutDial->setContentsMargins({0,0,0,0});

    dialTemp=new DialImage(this);
    dialTemp->setObjectName("dialTemp");
    dialTemp->setValue("温度",22);
    hlayoutDial->addWidget(dialTemp);

    dialHumidity=new DialImage(this);
    dialHumidity->setObjectName("dialTemp");
    dialHumidity->setValue("温度",22);
    hlayoutDial->addWidget(dialHumidity);

    hlayoutSimpleInfo->addLayout(hlayoutDial);
}

void SimpleWeatherInfo::setWeatherInfo(std::string name,std::string value)
{
    if(0 == name.compare("weatherico"))
    {
        labelWeatherImg->setStyleSheet(QString("image:url(:/weathericons/resource/weathericons/%1.png);")
                                       .arg(value.data()));
        return;
    }
    auto it = mapInfoLabel.find(name);
    if(it!=mapInfoLabel.end())
        it->second->setText(value.c_str());
}

void SimpleWeatherInfo::timingMove()
{
    // 3s周期响应
    if(10000==timer.interval())
    {
        timer.stop();
        timer.setInterval(400);
        timer.start();
    }
    else if(400 == timer.interval())
    {
        startX-=5;
        if(abs(startX) % 900 == 0)
        {
            timer.stop();
            timer.setInterval(10000);
            startX=0;
            timer.start();
        }
        this->update();
    }
}
