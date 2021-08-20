#include "roomenvironmentmonitor.h"
#include "code/common/comdefine.h"

RoomEnvironmentMonitor::RoomEnvironmentMonitor(QWidget *parent)
    : QWidget(parent)
{
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    initialControl();    

	Common::setRootWidget(this);

    initNetworkConfig();
}

RoomEnvironmentMonitor::~RoomEnvironmentMonitor()
{

}

void RoomEnvironmentMonitor::resizeEvent(QResizeEvent *event)
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

    //simpleinfo->setFixedSize(Common::tranWidth())

	infoToday->setFixedSize(Common::tranWidth(540), Common::tranHeight(300));

    preipitationForececast->setFixedSize(Common::tranWidth(540),Common::tranHeight(300));

    QWidget::resizeEvent(event);
}

void RoomEnvironmentMonitor::initialControl()
{
    this->setStyleSheet("background-color:rgba(14,58,96,183);"
                        "border:0px;");
    this->resize(712,400);

    gridlayoutMain=new QGridLayout(this);
    gridlayoutMain->setContentsMargins({64,33,64,46});

    // 顶部位置信息
    topinfo=new TopInfo(this);

    // 简要天气信息
    simpleinfo=new SimpleWeatherInfo(this);

    // 今日信息
	infoToday = new WeatherInfoToday(this);

    // 降水预报
	preipitationForececast = new PrecipitationForecast(this);

    spacerItemTB=new QSpacerItem(20,40,QSizePolicy::Minimum,QSizePolicy::QSizePolicy::Expanding);



    gridlayoutMain->addWidget(topinfo,0,0,1,3);
    gridlayoutMain->addWidget(simpleinfo,1,0,1,3);
    gridlayoutMain->addWidget(infoToday,2,0,1,1);
	gridlayoutMain->addWidget(preipitationForececast, 2, 1, 1, 1);

    gridlayoutMain->addItem(spacerItemTB,3,0,1,2);

    this->setLayout(gridlayoutMain);
}

void RoomEnvironmentMonitor::initNetworkConfig()
{
    pNetManager=new QNetworkAccessManager(this);

    pNetRequest=new QNetworkRequest;

    QSslConfiguration config;
    config=pNetRequest->sslConfiguration();
    config.setProtocol(QSsl::SslProtocol::TlsV1SslV3);
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    pNetRequest->setSslConfiguration(config);

    //pNetRequest->setUrl(QUrl(QString("https://%1.%2/%3")\
                             .arg(REQUEST_DOMAIN_WEATHER)\
                             .arg(REQUEST_HOST)\
                             .arg("town/api/v1/sk?lat=36.06623&lng=120.38299")));

    pNetRequest->setUrl(QUrl(QString(REQUEST_URL)));

    pNetReply = pNetManager->get(*pNetRequest);
    connect(pNetReply,&QNetworkReply::readyRead,[&]()
    {
        qDebug()<<pNetReply->rawHeaderList();
        qDebug()<<pNetReply->rawHeader("content-length");
        QByteArray data;
        data=pNetReply->readAll();

        QJsonDocument jsdoc=QJsonDocument::fromJson(data);
        QJsonObject jsobj=jsdoc.object();
        string value;
        auto it = jsobj.find("responses");
        if(it!=jsobj.end())
        {
            auto it_=it.value().toArray()[0].toObject()["weather"].toArray()[0].toObject()["current"].toObject();
            value=it_["cap"].toString().toStdString();
            simpleinfo->setWeatherInfo("weather",value);
            string content;
            content = Common::readFileContent("G:/Programming/C++_Qt/RoomEnvironmentMonitor/code/weathercodemap.json");
            QJsonParseError jserror;
            jsdoc=QJsonDocument::fromJson(content.data(),&jserror);
            if(jserror.error!=QJsonParseError::NoError)
            {
                return ;
            }
            jsobj = jsdoc.object();
            it = jsobj.find(value.c_str());
            if(it!=jsobj.end())
            {
                simpleinfo->setWeatherInfo("weatherico",it.value().toObject().value("code").toString().toStdString());
            }
            value=QString::number(it_["temp"].toInt()).toStdString();
            if(it!=jsobj.end())
                simpleinfo->setWeatherInfo("temp",value + "℃");

        }



    });
}