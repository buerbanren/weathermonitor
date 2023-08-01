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
#include <QPushButton>
#include <QFile>

#define RAINFALLRADAR_DATA_DOMAIN "http://d1.weather.com.cn/newwebgis/radar/"
#define RAINFALLRADAR_DATA_PATH "radar_list_new.json?_=1633345386515"

// 动态库导出接口
extern "C" INTERFACE_EXPORT CPluginInterface* getInstall();

enum ZoomType
{
    ZoomIn = 1, //放大
    ZoomOut // 缩小
};

class QCefWidget;

class AchieveClass: public CPluginInterface
{
	Q_OBJECT
public:
    AchieveClass();
	~AchieveClass()override;

    // 获取插件界面
    virtual QWidget *getPluginWidget();

    // 获取插件应用图标
    virtual QImage getPluginIcon();

    virtual void getPluginInfo(stuPluginInfo &info);

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
    void radarZoom(ZoomType type);
    
	void saveRadarImage(QImage &radar, std::string time);

	void updateImageList(std::vector<std::string> timelist);
	
	QWidget *widget=nullptr;

private:
    QNetworkAccessManager *pnetmanager=nullptr;
    QNetworkRequest *pnetrequest=nullptr;
    QNetworkReply *pnetreply=nullptr;

    QByteArray radardata;

    std::map<std::string,std::string> mapRainfallForImg;
    std::map<std::string, QImage> mapRainfallImg;
    QRect radarImageRect;

    // 单张图片数据
    QByteArray imgdata;
    std::list<std::string> list_time;
    QTimer timerRainfallPlay;
    std::map<std::string, QImage>::iterator radarIterator;
    QLabel *imagelabel=nullptr;
    QPushButton *pbtZoomIn=nullptr;
    QPushButton *pbtZoomOut=nullptr;


	QWidget *cefWidget = nullptr;
};

#endif // ACHIEVE_H
