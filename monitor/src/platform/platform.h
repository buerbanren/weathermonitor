#pragma once

#include <QWidget>

class Platform
{
public:
	static void initCefBrowser();

	static QWidget createCefBrowser();

};
