#include "weathermonitor.h"
#include "src/common/comdefine.h"

#include <QDebug>
#include <QCryptographicHash>

WeatherMonitor::WeatherMonitor(QWidget *parent)
    : QWidget(parent)
{
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    initialControl();

	Common::setRootWidget(this);

    startNetworkConfig();

}

WeatherMonitor::~WeatherMonitor()
{

}

void WeatherMonitor::addPluginPage(QWidget * const widget)
{
    if(!widget)
        return;
    widget->show();
    for(int i=0;i<vetPluginPageStatus.size();i++)
    {
        if( true == vetPluginPageStatus.at(i))
        {
            continue;
        }
        widget->lower();
        gridlayoutMain->addWidget(widget, 3,i,1,1);
        vetPluginPageStatus[i]=true;
        break;
    }
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

void WeatherMonitor::resolveResponseWeather()
{
    jsdoc = QJsonDocument::fromJson(jsdata);
    jsobj=jsdoc.object();
    string value;

        // 当前天气信息
        auto weather_current = jsobj["responses"].toArray()[0].toObject()["weather"].toArray()[0].toObject()["current"].toObject();
        value=weather_current["capAbbr"].toString().toStdString();
        simpleinfo->setWeatherInfo("weather",value);

        // 天气icon配置文件
        string content;
        content = Common::readFileContent("../../monitor/src/weathercodemap.json");
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

    {
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

    /*
     * 24小时天气预报
     */
    auto weather_days=weather_forecast.value("days").toArray();

    std::vector<HourInfo> hoursdata;

    for(int i=0;i<2;i++)
    {
        auto forecast_dayinfo=weather_days.at(i).toObject().value("hourly").toArray();
        auto ithour=forecast_dayinfo.begin();
        while(ithour!=forecast_dayinfo.end())
        {
            QString valueTime=ithour->toObject().value("valid").toString();
            QDateTime qdateTime=QDateTime::fromString(valueTime ,"yyyy-MM-ddThh:mm:ss+08:00");
            valueTime=qdateTime.toString("hh");

            // 天气类型，需要转换为对应图标路径
            QString cap=ithour->toObject().value("cap").toString();
            int temp=ithour->toObject().value("temp").toInt();

            hoursdata.push_back({valueTime.toInt(),cap,temp});

            if(hoursdata.size()==24)
                break;
            ithour++;
        }
        if(hoursdata.size()==24)
            break;
    }
    // 设置未来24小时预报信息
    preipitationForececast->setHoursInfo(hoursdata);

    /*
     * 未来一周天气预报
     * 包含天气、风向、风力、温度
     *
     */
    auto weather_week=weather_forecast.value("days").toArray();

    std::vector<DayInfo> weekdaydata;

    for(int i=0;i<7;i++)
    {
        auto totalInfo=weather_week.at(i).toObject().value("daily").toObject();
        // 日期
        string str_dateTime=totalInfo.value("valid").toString().toStdString(); // 2021-09-11T11:00:00+08:00
        QDateTime _dateTime=QDateTime::fromString(str_dateTime.substr(0,10).data(),"yyyy-MM-dd");
        str_dateTime=_dateTime.toString("MM-dd").toStdString();

        // 天气类型
        string weatherIcoTtype=totalInfo.value("pvdrCap").toString().toStdString();

        // 风力及风向
        string windDir=totalInfo.value("pvdrWindDir").toString().toStdString();
        string windSpeed=totalInfo.value("pvdrWindSpd").toString().toStdString();

        // 最高最低温
        int tempHi=totalInfo.value("tempHi").toInt();
        int tempLO=totalInfo.value("tempLo").toInt();

        DayInfo tempinfo={str_dateTime,Common::convertIcoType2Path(weatherIcoTtype),
                              windDir,windSpeed,tempLO,tempHi};

        weekdaydata.push_back(tempinfo);

    }
    weekendForecast->setDaysInfo(weekdaydata);

    jsdata.clear();
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
        int pos = it.indexOf(simpleinfo->getDistrict().data());
        if(-1 == pos)
            continue;

        it = _it.toObject().find("description")->toString();
        if( -1 == it.indexOf("发布"))
            continue;
        simpleinfo->setWeatherInfo("warn",it.toStdString());
        break;
    }
    jsdataWarn.clear();
}

void WeatherMonitor::resolveResponseLocation()
{
    // 提取ip地址
    QRegExp ipreg("(([0-9]){1,}\.([0-9]){1,}\.([0-9]){1,}\.([0-9]){1,}){1}");
    qDebug()<<locationData;
    if(-1 == ipreg.indexIn(locationData,0))
    {
        qDebug()<<"IP address lost";
        return;
    }
    strIP = ipreg.cap(1).toStdString();
    qDebug()<<"local host ip:"<<strIP.c_str();

    // 拼接请求参数
    // 密钥串：/ws/location/v1/ip?ip=""&key=""+sk&sig=""
    std::string keysk;
    keysk.append(TENCENT_LOCATIONPATH);
    keysk.append("ip=");
    keysk.append(strIP);
    keysk.append("&key=");
    keysk.append(TENCENT_URL_TOKEN);
    keysk.append(TENCENT_URL_SK);

    QByteArray data=QByteArray::fromStdString(keysk);
    qDebug()<<keysk.data();
	// 签名
    string strSig = QCryptographicHash::hash(data,QCryptographicHash::Md5).toHex().toStdString();

    keysk.append("&sig=");
    keysk.append(strSig.data());

    std::string requestUrl;
    requestUrl.append(TENCENT_LOCATIONHOST);
    requestUrl.append(TENCENT_LOCATIONPATH);
    requestUrl.append("ip=");
    requestUrl.append(strIP);
    requestUrl.append("&key=");
    requestUrl.append(TENCENT_URL_TOKEN);
    requestUrl.append("&sig=");
    requestUrl.append(strSig);

    QSslConfiguration config;
    config=pNetRequestLocation->sslConfiguration();
    config.setProtocol(QSsl::SslProtocol::TlsV1SslV3);
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    pNetRequestLocation->setSslConfiguration(config);

    qDebug()<<requestUrl.data();
    pNetRequestLocation->setUrl(QUrl(requestUrl.data()));

	pNetReplyTencentLocation = pNetManager->get(*pNetRequestLocation);

	locationData.clear();
    connect(pNetReplyTencentLocation, &QNetworkReply::readyRead, [=]()
	{
		locationData.append(pNetReplyTencentLocation->readAll());
	});
    connect(pNetReplyTencentLocation, &QNetworkReply::finished, [=]()
	{
		qDebug() << locationData.data();
        QJsonDocument locationJson=QJsonDocument::fromJson(locationData);
        if(!locationJson.isObject())
            return ;
        QJsonObject jsobj=locationJson.object();
        auto it=jsobj.find("status").value().toInt();
        if(it!=0)
        {
            qDebug()<<"error:"<<jsobj.find("message").value().toString();
            return ;
        }
        double lon=jsobj.find("result").value().toObject().value("location").toObject().value("lng").toDouble();
        double lat=jsobj.find("result").value().toObject().value("location").toObject().value("lat").toDouble();
        string province=jsobj.find("result").value().toObject().value("ad_info").toObject().value("province").toString().toStdString();
        string city=jsobj.find("result").value().toObject().value("ad_info").toObject().value("city").toString().toStdString();
        string district=jsobj.find("result").value().toObject().value("ad_info").toObject().value("district").toString().toStdString();

        topinfo->setCityInfo(district);

        Common::setMsgWeatherUrl(lat,lon);

        simpleinfo->setDistrict(district);

        requestWeatherInfo();
	});

}

void WeatherMonitor::requestWeatherInfo()
{
    // 今日天气详情请求
    QSslConfiguration config;
    config=pNetRequest->sslConfiguration();
    config.setProtocol(QSsl::SslProtocol::TlsV1SslV3);
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    pNetRequest->setSslConfiguration(config);

    pNetRequest->setUrl(QUrl(QString(Common::getMsnWeatherUrl().data())));

    pNetReply = pNetManager->get(*pNetRequest);
    // 今日天气信息获取
    connect(pNetReply,&QNetworkReply::readyRead,[&]()
    {
       jsdata.append(pNetReply->readAll());
    });

    // 响应完成解析数据
    connect(pNetReply,&QNetworkReply::finished,this,&WeatherMonitor::resolveResponseWeather);


    // 预警信息请求
    pNetRequestWarn->setUrl(QUrl(QString(QString(REQUEST_ALARM_URL))));

    pNetReplyWarn=pNetManager->get(*pNetRequestWarn);
    connect(pNetReplyWarn,&QNetworkReply::readyRead,[&]()
    {
        jsdataWarn.append(pNetReplyWarn->readAll());
    });

    connect(pNetReplyWarn,&QNetworkReply::finished,this,&WeatherMonitor::resolveResponseWarn);
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

    // 网络初始化
    pNetManager=new QNetworkAccessManager(this);
    pNetRequestLocation=new QNetworkRequest;

    pNetRequest=new QNetworkRequest;
    pNetRequestWarn=new QNetworkRequest;
}

void WeatherMonitor::startNetworkConfig()
{
    info.setText("最近更新时间:"+QDateTime::currentDateTime().toString());
    info.setModal(false);
    //info.show();

    // ip地址转行政区域
    pNetRequestLocation->setUrl(QUrl(QString(REQUEST_LOCALIPURL)));

    pNetReplyLocation = pNetManager->get(*pNetRequestLocation);

    connect(pNetReplyLocation,&QNetworkReply::readyRead,[&]()
    {
        locationData.append(pNetReplyLocation->readAll());
    });
    connect(pNetReplyLocation,&QNetworkReply::finished,this,&WeatherMonitor::resolveResponseLocation);

}
