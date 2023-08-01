#ifndef PLATFORM_H
#define PLATFORM_H

#include "platform_global.h"

class QWidget;

class PLATFORM_EXPORT Platform
{
public:
    Platform();

	// 初始化Cef
	static int initCef();

	// 释放Cef
	static void releaseCef();

	// 创建cef窗口
	static QWidget* createCefWidget();
};

#endif // PLATFORM_H
