#include "achieve.h"
#include <QMessageBox>
#include <QPainter>

TestInterface *testInterface=nullptr;

TestInterface* getInstall()
{
    if(!testInterface)
        testInterface=new AchieveClass();

    return testInterface;
}

AchieveClass::AchieveClass()
{
    std::string qssstyledata;

    QFile qssfile(":/pluginprecipitationradar/src/resource/qss/plugin.qss");
    if(qssfile.open(QFile::OpenModeFlag::ReadOnly))
    {
        qssstyledata=qssfile.readAll().toStdString();
    }

    widget=new QWidget(nullptr);
    widget->resize(100,50);
    widget->setStyleSheet(qssstyledata.data());

    pnetmanager=new QNetworkAccessManager(widget);

    QString strurl;
    strurl.append(RAINFALLRADAR_DATA_DOMAIN);
    strurl.append(RAINFALLRADAR_DATA_PATH);
    pnetrequest=new QNetworkRequest(QUrl(strurl));
    pnetrequest->setRawHeader("Referer","http://www.weather.com.cn/");

    // 请求数据并解析雷达数据列表
    requestRadarData();

    connect(this,&AchieveClass::imgdataFinished,[=](std::string key)
    {
        requestImageData(key);
    });

    timerRainfallPlay.setInterval(500);

    connect(&timerRainfallPlay,&QTimer::timeout, this, &AchieveClass::playRadarImage);

    imagelabel=new QLabel(widget);
    imagelabel->move(0,0);
    imagelabel->show();

    // 雷达图放大
    pbtZoomIn=new QPushButton(widget);
    pbtZoomIn->setObjectName("btZoomIn");
    pbtZoomIn->move(10,10);
    pbtZoomIn->setFixedSize(20,20);
    pbtZoomIn->show();
    connect(pbtZoomIn,&QPushButton::clicked,[=]()
    {
        radarZoom(ZoomType::ZoomIn);
    });

    // 雷达图缩小
    pbtZoomOut=new QPushButton(widget);
    pbtZoomOut->setObjectName("btZoomOut");
    pbtZoomOut->move(10,40);
    pbtZoomOut->setFixedSize(20,20);
    pbtZoomOut->show();
    connect(pbtZoomOut,&QPushButton::clicked,[=]()
    {
        radarZoom(ZoomType::ZoomOut);
    });
}

QWidget *AchieveClass::getPluginWidget()
{
    return this->widget;
}

QImage AchieveClass::getPluginIcon()
{
    return QImage(":/pluginprecipitationradar/src/resource/qss/weatherradar.png");
}

void AchieveClass::getPluginInfo(stuPluginInfo &info)
{
    info.ico=getPluginIcon();
    info.name="降水雷达";
    info.version="0.0.1";
    info.copyright="";
    info.lastTime="2021-11-18";
    info.description="此插件提供由雷达探测云层信息后推算出的全国各地区降水概率情况，包含未来的24小时降水量";
}

AchieveClass::~AchieveClass()
{
    if(widget)
    {
		delete widget;
        widget=nullptr;
        //QMessageBox::information(NULL,"提示","已被释放");
    }
}

void AchieveClass::requestRadarData()
{
    pnetreply = pnetmanager->get(*pnetrequest);

    connect(pnetreply,&QNetworkReply::readyRead,[=]()
    {
        radardata.append(pnetreply->readAll());
    });
    connect(pnetreply,&QNetworkReply::finished,[=]()
    {
        // QMessageBox::information(nullptr, "数据", this->radardata);
        analysisRadarData(radardata);
        radardata.clear();

        // 将所有预报点压入队列
        for(auto iturl:mapRainfallForImg)
        {
            list_time.push_back(iturl.first);
        }
        std::string firstkey = * (list_time.begin());
        list_time.pop_front();

        emit imgdataFinished(firstkey);
    });
}

void AchieveClass::analysisRadarData(QByteArray data)
{
    QRegExp regexp("[A-Za-z0-9]+\ [A-Za-z0-9]+\ =");
    QString strjsdata=data;
    int pos=0;
    int count=0;
    if((pos=regexp.indexIn(strjsdata,pos)) == -1)
    {
        qDebug()<<"变量排除错误";
        return;
    }
	count = regexp.matchedLength();
    //data= strjsdata.fromRawData(&(strjsdata.data()[pos+count]), strjsdata.size()-(pos+count));
	strjsdata = strjsdata.fromLatin1(&(strjsdata.toStdString().at(pos+count)), strjsdata.size() - (pos + count));

    QJsonDocument jsdoc;
    QJsonParseError jserror;
    jsdoc=QJsonDocument::fromJson(strjsdata.toStdString().data(),&jserror);
    if(jserror.error != QJsonParseError::NoError)
    {
        qDebug()<<"降水雷达数据错误"<<jserror.errorString();
        return;
    }
    auto radarobj=jsdoc.object();

    // 雷达数据生成时间
    std::string radartime;
    if(radarobj.find("stime")==radarobj.end())
    {
        //qDebug()<<"键错误";
        return;
    }
    radartime=radarobj.find("stime").value().toString().toStdString();

    // 具体内容
    auto valuearr=radarobj.find("value");
    if(valuearr ==radarobj.end()){
        //qDebug()<<"键错误";
        return;
    }
    if(!valuearr->isArray())
    {
        //qDebug()<<"雷达数据非数组类型";
        return;
    }
    std::map<std::string,std::string> mapEmpty;
    mapRainfallForImg.swap(mapEmpty);

    for(auto valuedayobj: valuearr.value().toArray())
    {
		if (!valuedayobj.isObject())
			return;
	
		std::string date= valuedayobj.toObject().take("date").toArray().at(0).toString().toStdString();
        QDateTime datehour=QDateTime::fromString(date.data(),"yyyyMMddhh");
        if(datehour.time().hour() < QTime::currentTime().hour())
        {
            // 忽略小于当前是时刻的数据
            continue;
        }

        auto timearray=valuedayobj.toObject().value("time").toArray();
        auto timepatharay=valuedayobj.toObject().value("path").toArray();
        for(int indexTime=0;indexTime<timearray.size();indexTime++)
        {
            mapRainfallForImg[timearray.at(indexTime).toString().toStdString()]=\
                    timepatharay.at(indexTime).toString().toStdString();
        }
    }
}

void AchieveClass::requestImageData(std::string key)
{
    {
		// image 网络地址
		std::string imgurl;
		imgurl.append(RAINFALLRADAR_DATA_DOMAIN);
        imgurl.append(mapRainfallForImg.at(key));

		pnetrequest->setUrl(QUrl(imgurl.data()));
		pnetrequest->setRawHeader("Referer", "http://www.weather.com.cn/");
		pnetreply = pnetmanager->get(*pnetrequest);
		
		connect(pnetreply, &QNetworkReply::readyRead, [=]()
		{
			imgdata.append(pnetreply->readAll());
		});
		connect(pnetreply, &QNetworkReply::finished, [=]()
        {
			QImage img;
			img.loadFromData(imgdata);
            radarImageRect={0,0,img.width(),img.height()};
            imgdata.clear();

            mapRainfallImg[key] = img;

            //img.save(QString("C:\\Users\\hp_db\\Desktop\\monitor\\%1.png").arg(key.data()));

            // 始终获取队列的第一个时间点，为空时代表结束
            if(0 == list_time.size())
            {
                if(mapRainfallImg.size()!=0)
                    timerRainfallPlay.start();
                radarIterator=mapRainfallImg.begin();
                imagelabel->resize(widget->size());
                return ;
            }
            std::string curtime = * (list_time.begin());
            list_time.pop_front();
            emit imgdataFinished(curtime);
		});
    }
}

void AchieveClass::radarZoom(ZoomType type)
{
    int zoomSizeWH=0;
    switch (type) {
    case ZoomType::ZoomIn://放大
        zoomSizeWH=50;
        break;
    case ZoomType::ZoomOut://缩小
        zoomSizeWH=-50;
        break;
    }
    radarImageRect.setX(radarImageRect.x()+zoomSizeWH);
    radarImageRect.setY(radarImageRect.y()+zoomSizeWH);
    radarImageRect.setWidth(radarImageRect.width()-(zoomSizeWH*2));
    radarImageRect.setHeight(radarImageRect.height()-(zoomSizeWH*2));

}

void AchieveClass::playRadarImage()
{
    if(radarIterator==mapRainfallImg.end())
    {
        radarIterator=mapRainfallImg.begin();
    }

    //imagelabel->setPixmap(QPixmap("C:\\Users\\hp_db\\Desktop\\monitor\\0020.png"));
    QImage radarimg;
    radarimg=radarIterator->second.copy(radarImageRect);
    imagelabel->setPixmap(QPixmap::fromImage(radarimg.scaled(widget->size())));

    radarIterator++;
}
