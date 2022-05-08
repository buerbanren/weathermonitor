#include "plugininfo.h"
#include "../common/comdefine.h"

PluginInfo::PluginInfo(TestInterface *testInterface, QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet(Common::readFileContent(":/qss/resource/qss/plugininfo.css").data());
    init();
}

void PluginInfo::init()
{
    vlayout_info=new QVBoxLayout(this);
    vlayout_info->setContentsMargins(10,10,10,30);
    vlayout_info->setSpacing(0);
    this->setLayout(vlayout_info);

    // 顶部返回栏
    frame_infotop=new QWidget(this);
    frame_infotop->setFixedHeight(32);
    hlayout_infotop=new QHBoxLayout(frame_infotop);
    hlayout_infotop->setContentsMargins(0,0,0,0);
    hlayout_infotop->setSpacing(0);

    btReturn=new QPushButton(frame_infotop);
    btReturn->setObjectName("bt_returnPluginALL");
    btReturn->setFixedSize(32,32);
    connect(btReturn,&QPushButton::clicked,[=]()
    {
        emit returnPluginPage();
    });
    hlayout_infotop->addWidget(btReturn,0,Qt::AlignVCenter);

    hspacer_info=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    hlayout_infotop->addItem(hspacer_info);

    vlayout_info->addWidget(frame_infotop);

    // 插件信息栏
    frame_infocontent=new QWidget(this);
    frame_infocontent->setStyleSheet("background-color:red");
    vlayout_info->addWidget(frame_infocontent);

    QLabel *labPluginIco;



}
