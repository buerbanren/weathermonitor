#include "monitormenu.h"
#include "../common/comdefine.h"

MonitorMenu::MonitorMenu(QWidget *parent) : QFrame(parent)
{
    this->setMinimumSize(Common::tranWidth(960),Common::tranHeight(210));

    this->setObjectName("MonitorMenu");

    this->setStyleSheet(Common::readFileContent(":/qss/resource/qss/monitormenu.css").data());

    initUILayout();

    connect(btgroupMenu,static_cast<void(QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked),[=](QAbstractButton *button)
    {
        for(auto bt : mapMenuControl)
        {
            bt.second.button->setStyleSheet("background:transparent;");
            bt.second.label->setStyleSheet("background:transparent;");
        }
        std::string name=button->property("name").toString().toStdString();
        mapMenuControl.at(name).button->setStyleSheet("background-color:gray;");
        mapMenuControl.at(name).label->setStyleSheet("color:white;");
        emit menuChanged(name);
    });

    this->move((parentWidget()->width()-this->width())/2,parentWidget()->height()-36);
}

void MonitorMenu::initUILayout()
{
    StructMenu structMenuitem;
    pgridlayoutMainMenu=new QGridLayout(this);
    pgridlayoutMainMenu->setContentsMargins({32,8,32,8});

    // 上拉窗口按键
    pbtUpload=new QPushButton(this);
    pbtUpload->setFixedSize(46,22);
    pbtUpload->setObjectName("btUpWidget");
    pgridlayoutMainMenu->addWidget(pbtUpload, 0, 1, 1, 2, Qt::AlignHCenter);
    connect(pbtUpload,&QPushButton::clicked,[=]()
    {
        pgridlayoutMainMenu->setContentsMargins({32,32,32,0});
        this->move((parentWidget()->width()-this->width())/2,(parentWidget()->height()-this->height())/2);
        pbtUpload->hide();
        pbtDownload->show();
    });

    btgroupMenu=new QButtonGroup(this);

    // 软件退出
	pbtExit = new QPushButton(this);
    pbtExit->setFixedSize(46,46);
    pbtExit->setProperty("name","exit");
    pbtExit->setObjectName("btExit");
    btgroupMenu->addButton(pbtExit);
    pgridlayoutMainMenu->addWidget(pbtExit,1,0);
    structMenuitem.button=pbtExit;
	
	plabExit = new QLabel("关闭", this);
	plabExit->setFixedSize(46, 24);
	plabExit->setProperty("name", "exit");
    plabExit->setAlignment(Qt::AlignCenter);
    pgridlayoutMainMenu->addWidget(plabExit,2,0);
    structMenuitem.label=plabExit;
    mapMenuControl["exit"]=structMenuitem;

    // 插件区
	pbtPlugin = new QPushButton(this);
    pbtPlugin->setFixedSize(46,46);
    pbtPlugin->setProperty("name","plugin");
    pbtPlugin->setObjectName("btPlugin");
    btgroupMenu->addButton(pbtPlugin);
    pgridlayoutMainMenu->addWidget(pbtPlugin,1,1);
    structMenuitem.button=pbtPlugin;

	plabPlugin = new QLabel("插件", this);
    plabPlugin->setFixedSize(46,24);
    plabPlugin->setProperty("name","plugin");
    plabPlugin->setAlignment(Qt::AlignCenter);
    pgridlayoutMainMenu->addWidget(plabPlugin,2,1);
    structMenuitem.label=plabPlugin;
    mapMenuControl["plugin"]=structMenuitem;

    // 反馈区
	pbtFeedback = new QPushButton(this);
    pbtFeedback->setFixedSize(46,46);
    pbtFeedback->setProperty("name","feedback");
    pbtFeedback->setObjectName("btFeedback");
    btgroupMenu->addButton(pbtFeedback);
    pgridlayoutMainMenu->addWidget(pbtFeedback,1,2);
    structMenuitem.button=pbtFeedback;

	plabFeedback = new QLabel("反馈", this);
    plabFeedback->setFixedSize(46,24);
    plabFeedback->setProperty("name","feedback");
    plabFeedback->setAlignment(Qt::AlignCenter);
    pgridlayoutMainMenu->addWidget(plabFeedback,2,2);
    structMenuitem.label=plabFeedback;
    mapMenuControl["feedback"]=structMenuitem;

    // 关于区
    pbtAbout=new QPushButton(this);
    pbtAbout->setFixedSize(46,46);
    pbtAbout->setProperty("name","about");
    pbtAbout->setObjectName("btAbout");
    btgroupMenu->addButton(pbtAbout);
    pgridlayoutMainMenu->addWidget(pbtAbout,1,3);
    structMenuitem.button=pbtAbout;

    plabAbout=new QLabel("关于", this);
    plabAbout->setFixedSize(46,24);
    plabAbout->setProperty("name","about");
    plabAbout->setAlignment(Qt::AlignCenter);
    pgridlayoutMainMenu->addWidget(plabAbout,2,3);
    structMenuitem.label=plabAbout;
    mapMenuControl["about"]=structMenuitem;

    // 下拉窗口按键
    pbtDownload=new QPushButton(this);
    pbtDownload->setFixedSize(46,22);
    pbtDownload->setObjectName("btDownWidget");
    pgridlayoutMainMenu->addWidget(pbtDownload, 3, 1, 1, 2, Qt::AlignHCenter);
    connect(pbtDownload,&QPushButton::clicked,[=]()
    {
        pgridlayoutMainMenu->setContentsMargins({32,0,32,8});
        this->move((parentWidget()->width()-this->width())/2,parentWidget()->height()-36);
        pbtDownload->hide();
        pbtUpload->show();
        for(auto bt : mapMenuControl)
        {
            bt.second.button->setStyleSheet("background:transparent;");
            bt.second.label->setStyleSheet("background:transparent;");
        }
    });
}
