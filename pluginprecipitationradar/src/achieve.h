#ifndef ACHIEVE_H
#define ACHIEVE_H

#include "interface.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QDateTime>
#include <QTimer>
#include <QLabel>

#define RAINFALLRADAR_DATA_DOMAIN "http://d1.weather.com.cn/newwebgis/radar/"
#define RAINFALLRADAR_DATA_PATH "radar_list_new.json?_=1633345386515"

// 动态库导出接口
extern "C" INTERFACE_EXPORT TestInterface* getInstall();

class AchieveClass: public TestInterface
{
	Q_OBJECT
public:
    AchieveClass();

    // 获取插件界面
    virtual QWidget *getPluginWidget()override;

    // 获取插件应用图标
	virtual QImage getPluginIcon()override;

	~AchieveClass()override;

    // 播放降水雷达探测图
    void playRadarImage();

signals:
    void imgdataFinished(std::string key);

private:
    // 内部逻辑实现
    // 降水预报雷达数据请求
    void requestRadarData();

    void analysisRadarData(QByteArray data);
    void requestImageData(std::string key);
    QWidget *widget=nullptr;


private:
    QNetworkAccessManager *pnetmanager=nullptr;
    QNetworkRequest *pnetrequest=nullptr;
    QNetworkReply *pnetreply=nullptr;

    QByteArray radardata;

    std::map<std::string,std::string> mapRainfallForImg;
    std::map<std::string, QImage> mapRainfallImg;

    // 单张图片数据
    QByteArray imgdata;
    std::list<std::string> list_time;
    QTimer timerRainfallPlay;
    std::map<std::string, QImage>::iterator radarIterator;
    QLabel *imagelabel=nullptr;
};

#endif // ACHIEVE_H
