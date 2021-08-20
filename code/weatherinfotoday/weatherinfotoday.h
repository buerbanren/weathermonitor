#ifndef WEATHERINFOTODAY_H
#define WEATHERINFOTODAY_H

#include <map>
#include <QLabel>
#include <QGridLayout>
#include <iostream>

#include "code/iteminfobase/iteminfobase.h"

struct WeatherInfo
{
	int index;
	string name;
	string value;
	QLabel *labelType;
	QLabel *labelValue;
};

class WeatherInfoToday : public ItemInfoBase
{
    Q_OBJECT
public:
	WeatherInfoToday(QWidget *parent = nullptr);

protected:
	void resizeEvent(QResizeEvent *event);

private:

	QGridLayout *gridlayoutInfoToday = nullptr;

	map<string, WeatherInfo> mapInfoToday = {
		pair<string,WeatherInfo>("sensibletemperature",{ 0, u8"体感温度",u8"33℃", new QLabel(this), new QLabel(this) }),
		pair<string,WeatherInfo>("humidity",{ 1, u8"湿度",u8"90%",new QLabel(this),new QLabel(this) }),
		pair<string,WeatherInfo>("winddirection",{ 2, u8"风向",u8"北风",new QLabel(this),new QLabel(this) }),
		pair<string,WeatherInfo>("windpower",{ 3, u8"风力",u8"2级",new QLabel(this),new QLabel(this) }),
		pair<string,WeatherInfo>("ultravioletray",{ 4, u8"紫外线",u8"强",new QLabel(this),new QLabel(this) }),
		pair<string,WeatherInfo>("visibility",{ 5, u8"能见度",u8"0.1km",new QLabel(this),new QLabel(this) }),
		pair<string,WeatherInfo>("sunup",{ 6, u8"日出",u8"5:43",new QLabel(this),new QLabel(this) }),
		pair<string,WeatherInfo>("sunset",{ 7, u8"日落",u8"19:32",new QLabel(this),new QLabel(this) })
	};
	

};

#endif // WEATHERINFOTODAY_H
