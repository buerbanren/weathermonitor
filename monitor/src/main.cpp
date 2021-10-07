
#include <QApplication>

#include "uimanage.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    UIManage um;
    um.show();
    QObject::connect(&um,&UIManage::exit,&a,&QApplication::exit);

    return a.exec();
}
