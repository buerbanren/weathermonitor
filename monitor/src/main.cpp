
#include <QApplication>

#include "uimanage.h"
#include <platform.h>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a(argc, argv);

	Platform::initCef();

    UIManage um;
    um.show();
    QObject::connect(&um,&UIManage::exit,&a,&QApplication::exit);

	a.exec();

	Platform::releaseCef();

	return 0;
}
