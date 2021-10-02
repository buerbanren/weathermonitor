#include "achieve.h"
#include <QMessageBox>

TestInterface *testInterface=nullptr;

TestInterface* getInstall()
{
    if(!testInterface)
        testInterface=new AchieveClass();

    return testInterface;
}

AchieveClass::AchieveClass()
{
    widget=new QWidget(nullptr);
    widget->resize(100,50);
}

QWidget *AchieveClass::getPluginWidget()
{
	return widget;
}

QImage AchieveClass::getPluginIcon()
{
    return QImage(":/test/chinaweather.png");
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
