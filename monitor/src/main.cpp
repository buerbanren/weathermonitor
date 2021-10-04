
#include <QApplication>

#include "uimanage.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    UIManage um;
    um.show();

	return a.exec();
}
