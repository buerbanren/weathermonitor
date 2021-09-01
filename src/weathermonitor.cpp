#include "weathermonitor.h"
#include "src/common/comdefine.h"

#include <QMessageBox>

WeatherMonitor::WeatherMonitor(QWidget *parent)
    : QWidget(parent)
{
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    initialControl();    

	Common::setRootWidget(this);

    initNetworkConfig();
}

WeatherMonitor::~WeatherMonitor()
{

}

void WeatherMonitor::resizeEvent(QResizeEvent *event)
{
    if(!topinfo || !gridlayoutMain)
        return;

    int mLeft=0,mTop=0,mRight=0,mBottom=0;
	mLeft = Common::tranWidth(64);
    mTop= Common::tranHeight(33);
    mRight= Common::tranWidth(64);
    mBottom= Common::tranHeight(46);
    gridlayoutMain->setContentsMargins({mLeft,mTop,
                                       mRight,mBottom});

    topinfo->setFixedHeight(Common::tranHeight(32));

    simpleinfo->setFixedHeight(Common::tranHeight(320));

	infoToday->setFixedSize(Common::tranWidth(540), Common::tranHeight(300));

    preipitationForececast->setFixedSize(Common::tranWidth(540),Common::tranHeight(300));

    weekendForecast->setFixedSize(Common::tranWidth(540),Common::tranHeight(300));

    QWidget::resizeEvent(event);
}

void WeatherMonitor::resolveResponse()
{
    jsdoc = QJsonDocument::fromJson(jsdata);
    jsobj=jsdoc.object();
    string value;

        // 当前天气信息
        auto weather_current = jsobj["responses"].toArray()[0].toObject()["weather"].toArray()[0].toObject()["current"].toObject();
        value=weather_current["capAbbr"].toString().toStdString();
        simpleinfo->setWeatherInfo("weather",value);
        qDebug()<<value.c_str();

        // 天气icon配置文件
        string content;
        content = Common::readFileContent("../../src/weathercodemap.json");
        QJsonParseError jserror;
        QJsonDocument jsdoc_icons=QJsonDocument::fromJson(content.data(),&jserror);
        if(jserror.error!=QJsonParseError::NoError)
        {
            qDebug()<<u8"本地天气图标配置文件解析失败";
            return ;
        }

        // 天气图标
        auto jsvalueicons = jsdoc_icons.object();
        auto it = jsvalueicons.find(value.c_str());
        if(it!=jsvalueicons.end())
        {
            simpleinfo->setWeatherInfo("weatherico",it.value().toObject().value("code").toString().toStdString());
        }
        // 当前温度
        value=QString::number(weather_current["temp"].toInt()).toStdString();
        simpleinfo->setWeatherInfo("temp",value + "℃");
        // 空气质量
        value=weather_current["aqiSeverity"].toString().toStdString();
        simpleinfo->setWeatherInfo("airquality",value);


        // 预报信息
        auto weather_forecast = jsobj["responses"].toArray()[0].toObject()["weather"].toArray()[0].toObject()["forecast"].toObject();
        // 最高温度
        value=QString::number(weather_forecast["days"].toArray()[0].toObject()["daily"].toObject()["tempHi"].toInt()).toStdString();
        value.append(u8"℃ / ");
        // 最高最低气温
        value.append(QString::number(weather_forecast["days"].toArray()[0].toObject()["daily"].toObject()["tempLo"].toInt()).toStdString());
        value.append(u8"℃");
        simpleinfo->setWeatherInfo("tempmaxmin",value);


        // 设置今日信息
        // 体感温度
        value=QString::number(weather_current["feels"].toInt()).toStdString();
        infoToday->setWeatherInfo("sensibletemperature",value + u8"℃");
        // 设置湿度
        value=QString::number(std::round(weather_forecast["days"].toArray()[0].toObject()["daily"].toObject()["rhLo"].toDouble())).toStdString();
        infoToday->setWeatherInfo("humidity",value + "%");
        // 风向与风力
        value=weather_current["pvdrWindDir"].toString().toStdString();
        infoToday->setWeatherInfo("winddirection",value);
        value=weather_current["pvdrWindSpd"].toString().toStdString();
        infoToday->setWeatherInfo("windpower",value);

        // 能见度
        value=QString::number(weather_current["vis"].toDouble()).toStdString();
        infoToday->setWeatherInfo("visibility",value + "km");
        // 日出日落时间
        value=weather_forecast["days"].toArray()[0].toObject()["almanac"].toObject()["sunrise"].toString().toStdString();
        value = value.substr(11,5);
        infoToday->setWeatherInfo("sunrise",value);
        value=weather_forecast["days"].toArray()[0].toObject()["almanac"].toObject()["sunset"].toString().toStdString();
        value = value.substr(11,5);
        infoToday->setWeatherInfo("sunset",value);




}

void WeatherMonitor::resolveResponseWarn()
{
    jsdoc = QJsonDocument::fromJson(jsdataWarn);
    if(!jsdoc.isObject())
        return;

    jsobj=jsdoc.object();

    auto it = jsobj.find("alertData");
    if(it == jsobj.end())
        return;

    // 预警信息数组
    QJsonArray valueArrWarn=it.value().toArray();

    string value;


    // 遍历所有预警信息
    foreach (auto _it, valueArrWarn) {
        auto it = _it.toObject().find("headline")->toString();
        int pos = it.indexOf("宝山");
        if(-1 == pos)
            continue;

        it = _it.toObject().find("description")->toString();
        simpleinfo->setWeatherInfo("warn",it.toStdString());
        break;
    }
}

void WeatherMonitor::initialControl()
{
    this->setStyleSheet("background-color:rgba(14,58,96,183);"
                        "border:0px;");

    gridlayoutMain=new QGridLayout(this);
    gridlayoutMain->setContentsMargins({64,33,64,46});

    // 顶部位置信息
    topinfo=new TopInfo(this);
    gridlayoutMain->addWidget(topinfo,0,0,1,3);

    // 简要天气信息
    simpleinfo=new SimpleWeatherInfo(this);
    gridlayoutMain->addWidget(simpleinfo,1,0,1,3);

    // 今日信息
	infoToday = new WeatherInfoToday(this);
    gridlayoutMain->addWidget(infoToday,2,0,1,1);

    // 12小时预报
	preipitationForececast = new PrecipitationForecast(this);
    gridlayoutMain->addWidget(preipitationForececast, 2, 1, 1, 1);

    // 7天预报
    weekendForecast=new WeekendForecast(this);
    gridlayoutMain->addWidget(weekendForecast,2,2,1,1);

    spacerItemTB=new QSpacerItem(20,40,QSizePolicy::Minimum,QSizePolicy::QSizePolicy::Expanding);


    gridlayoutMain->addItem(spacerItemTB,3,0);

    this->setLayout(gridlayoutMain);
}

void WeatherMonitor::initNetworkConfig()
{
    pNetManager=new QNetworkAccessManager(this);

    // 今日天气详情请求
    pNetRequest=new QNetworkRequest;

    QSslConfiguration config;
    config=pNetRequest->sslConfiguration();
    config.setProtocol(QSsl::SslProtocol::TlsV1SslV3);
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    pNetRequest->setSslConfiguration(config);

    pNetRequest->setUrl(QUrl(QString(REQUEST_MSN_URL)));

    pNetReply = pNetManager->get(*pNetRequest);
    // 今日天气信息获取
    connect(pNetReply,&QNetworkReply::readyRead,[&]()
    {
       jsdata.append(pNetReply->readAll());
    });

    // 响应完成解析数据
    connect(pNetReply,&QNetworkReply::finished,this,&WeatherMonitor::resolveResponse);


    // 预警信息请求
    pNetRequestWarn=new QNetworkRequest;
    pNetRequestWarn->setUrl(QUrl(QString(QString(REQUEST_ALARM_URL))));

    pNetReplyWarn=pNetManager->get(*pNetRequestWarn);
    connect(pNetReplyWarn,&QNetworkReply::readyRead,[&]()
    {
        jsdataWarn.append(pNetReplyWarn->readAll());
    });

    connect(pNetReplyWarn,&QNetworkReply::finished,this,&WeatherMonitor::resolveResponseWarn);
}
