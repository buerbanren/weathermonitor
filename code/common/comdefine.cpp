#include "comdefine.h"

QWidget* Common::rootWidget = nullptr;

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
