#ifndef COMDEFINE_H
#define COMDEFINE_H

#include <QDebug>
#include <QWidget>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
 * 定义程序所使用的基准尺寸
 * 1920*1080
 */
#define BASE_WIDGET_WIDTH 1920.0
#define BASE_WIDGET_HEIGHT 1080.0

#define REQUEST_ALARM_URL "http://www.12379.cn/data/alarm_list_all.html"
#define REQUEST_HOST "weather.com.cn"
#define REQUEST_DOMAIN_PRECIPITATION "d1"
#define REQUEST_DOMAIN_WEATHER "forecast"
#define REQUEST_MSN_URL u8"https://api.msn.com/weather/overview?locale=zh-CN&lat=%1&lon=%2&units=C&region=CN&appId=9e21380c-ff19-4c78-b4ea-19558e93a5d3&apiKey=OkWqHMuutahBXs3dBoygqCjgXRt6CV4i5V7SRQURrT&ocid=weather-app-win&wrapOData=false"
#define REQUEST_GEONAME_URL "https://map.baidu.com/?newmap=1&qt=cen&b=12859000,4710000;12863000,4714000&l=15&t=1629722656494"
#define REQUEST_LOCALIPURL "http://myip.ipip.net"
#define TENCENT_LOCATIONHOST "https://apis.map.qq.com"
#define TENCENT_LOCATIONPATH "/ws/location/v1/ip?"
#define TENCENT_URL_TOKEN ""
#define TENCENT_URL_SK ""

class Common {

public:
	static void setRootWidget(QWidget *widget);
	static QWidget* getRootWidget();
	static int tranWidth(int width);
	static int tranHeight(int height);
    static string readFileContent(string filepath);
    static string convertIcoType2Path(string type);
    static void setMsgWeatherUrl(double _lat,double _lon);
    static string getMsnWeatherUrl();


private:
    static QWidget *rootWidget;

    static double lon;
    static double lat;
};


#endif // COMDEFINE_H
