#ifndef COMDEFINE_H
#define COMDEFINE_H

#include <QWidget>
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

#define REQUEST_HOST "weather.com.cn"
#define REQUEST_DOMAIN_PRECIPITATION "d1"
#define REQUEST_DOMAIN_WEATHER "forecast"
#define REQUEST_URL u8"https://api.msn.com/weather/overview?locale=zh-CN&lat=31.648744&lon=105.1739788&units=C&region=CN&appId=9e21380c-ff19-4c78-b4ea-19558e93a5d3&apiKey=OkWqHMuutahBXs3dBoygqCjgXRt6CV4i5V7SRQURrT&ocid=weather-app-win&wrapOData=false"
class Common {

public:
	static void setRootWidget(QWidget *widget);
	static QWidget* getRootWidget();
	static int tranWidth(int width);
	static int tranHeight(int height);
    static string readFileContent(string filepath);

private:
	static QWidget *rootWidget;

};

#endif // COMDEFINE_H
