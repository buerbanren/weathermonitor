#ifndef PLATFORM_H
#define PLATFORM_H

#include "platform_global.h"

class QWidget;

class PLATFORM_EXPORT Platform
{
public:
    Platform();

	// ��ʼ��Cef
	static int initCef();

	// �ͷ�Cef
	static void releaseCef();

	// ����cef����
	static QWidget* createCefWidget();
};

#endif // PLATFORM_H
