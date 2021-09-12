#include "comdefine.h"

QWidget* Common::rootWidget = nullptr;

double Common::lon=0;
double Common::lat=0;

void Common::setRootWidget(QWidget * widget)
{
	rootWidget = widget;
}

QWidget* Common::getRootWidget()
{
	return rootWidget;
}

int Common::tranWidth(int width)
{
	if (!rootWidget)
		return 0;
	return int((width / BASE_WIDGET_WIDTH)*rootWidget->width());
}

int Common::tranHeight(int height)
{
	if (!rootWidget)
		return 0;
	return int((height / BASE_WIDGET_HEIGHT)*rootWidget->height());
}

string Common::readFileContent(string filepath)
{
    string content;
    ifstream file;
    file.open(filepath,fstream::in);
    if(!(file.is_open()))
    {
        return string();
    }
    char buffer[1024]={"\0"};
    while(file.getline(buffer,1024))
    {
        content.append(buffer);
        memset(buffer,0,1024);
    }
    file.close();
    return content;
}

string Common::convertIcoType2Path(string type)
{
    string icoPath=":/weathericons/resource/weathericons/";
    // 天气icon配置文件
    string content;
    content = Common::readFileContent("../../src/weathercodemap.json");
    QJsonParseError jserror;
    QJsonDocument jsdoc_icons=QJsonDocument::fromJson(content.data(),&jserror);
    if(jserror.error!=QJsonParseError::NoError)
    {
        qDebug()<<u8"本地天气图标配置文件解析失败";
        return "";
    }

    // 天气图标
    auto jsvalueicons = jsdoc_icons.object();
    auto it = jsvalueicons.find(type.c_str());
    if(it!=jsvalueicons.end())
    {
        icoPath.append(it.value().toObject().value("code").toString().toStdString());
        icoPath.append(".png");
        return icoPath;
    }

    return "";
}

void Common::setMsgWeatherUrl(double _lat, double _lon)
{
    lat=_lat;
    lon=_lon;
}

string Common::getMsnWeatherUrl()
{
    return QString(REQUEST_MSN_URL).arg(lat).arg(lon).toStdString();
}
