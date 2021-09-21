#include "pluginmanage.h"
#include "../common/comdefine.h"
#include "../../../plugindynamiclinklibrary/interface.h"
#include <QEvent>

typedef TestInterface* (*TestFunction)(QWidget*);

PluginManage::PluginManage(QWidget *parent) : QFrame(parent)
{
    this->setObjectName("FramePluginManage");

    this->setStyleSheet(Common::readFileContent(":/qss/resource/qss/pluginmanage.css").data());
    this->resize(Common::tranSize(800,580));

    initUILayout(this);
}

void PluginManage::initUILayout(QWidget *parent)
{
    p_vlayout=new QVBoxLayout(this);
    p_vlayout->setContentsMargins(0,0,0,0);
    p_vlayout->setSpacing(0);

    p_frameTop=new QFrame(this);
    p_frameTop->setObjectName("frameTop");
    p_hlayoutTop=new QHBoxLayout(p_frameTop);
    p_hlayoutTop->setContentsMargins({0,0,0,0});
    p_frameTop->setLayout(p_hlayoutTop);
    p_frameTop->setFixedHeight(Common::tranHeight(60));


    p_hlayoutTop->addSpacing(16);

    p_labPluginTitle=new QLabel(this);
    p_labPluginTitle->setObjectName("labPluginTitle");
    p_labPluginTitle->setText("插件管理");
    p_hlayoutTop->addWidget(p_labPluginTitle);

    p_hSpacerTop=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Preferred);
    p_hlayoutTop->addSpacerItem(p_hSpacerTop);

    p_btClose=new QPushButton(this);
    p_btClose->setObjectName("btClose");
    p_btClose->setFixedSize(Common::tranSize(36,36));
    p_btClose->setIconSize(p_btClose->size());
    connect(p_btClose,&QPushButton::clicked,this, &PluginManage::close);
    p_hlayoutTop->addWidget(p_btClose);

    p_hlayoutTop->addSpacing(16);

    p_vlayout->addWidget(p_frameTop);


    p_gridLayoutPlugin=new QGridLayout(this);
    p_gridLayoutPlugin->setMargin(0);
    p_gridLayoutPlugin->setHorizontalSpacing(Common::tranWidth(60));
    p_gridLayoutPlugin->setVerticalSpacing(Common::tranHeight(32));
    p_gridLayoutPlugin->setContentsMargins(Common::tranWidth(80),Common::tranHeight(40),
                                         Common::tranWidth(80),Common::tranHeight(40));

    p_btPluginAdd=new QPushButton(this);
    p_btPluginAdd->setFixedSize(Common::tranSize(125,125));
    p_gridLayoutPlugin->addWidget(p_btPluginAdd,0,0);
    connect(p_btPluginAdd,&QPushButton::clicked,this,&PluginManage::loadPluginDLL);

    p_btPluginAdd2=new QPushButton(this);
    p_btPluginAdd2->setFixedSize(Common::tranSize(125,125));
    p_gridLayoutPlugin->addWidget(p_btPluginAdd2,0,1);
    connect(p_btPluginAdd2,&QPushButton::clicked,this,&PluginManage::loadPluginDLL);

    p_hSpacer=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Preferred);
    p_gridLayoutPlugin->addItem(p_hSpacer,0,2,1,2);

    p_vSpacer=new QSpacerItem(20,40,QSizePolicy::Preferred,QSizePolicy::Expanding);
    p_gridLayoutPlugin->addItem(p_vSpacer,1,0,2,4);

    p_vlayout->addLayout(p_gridLayoutPlugin);

}

void PluginManage::loadPluginDLL()
{
    // DLL加载测试
    TestFunction getInstall=(TestFunction)QLibrary::resolve("test","getInstall");
    if(!getInstall)
     {
        QMessageBox::warning(this,"提示","接口获取失败");
        return;
    }

    QMessageBox::warning(this,"提示","DLL载入成功");
    TestInterface *testInterface=getInstall(testWidget);

    if(!testInterface)
        return;

    QMessageBox::warning(this,"提示","接口调用成功");

    testWidget=testInterface->getPluginWidget();
    testWidget->hide();
    testWidget->setStyleSheet("background-color:red;");
    testWidget->show();

    p_btPluginAdd->setStyleSheet(Common::readFileContent(":/qss/resource/qss/pluginmanagebt.css").data());
    p_btPluginAdd->setIconSize(p_btPluginAdd->size());
    p_btPluginAdd->setIcon(QIcon(QPixmap::fromImage(testInterface->getPluginIcon())));

}

bool PluginManage::event(QEvent *event)
{
    // 窗口位置拖动
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    {
        pressed=true;
        posCursor=QCursor::pos();
    }
        break;
    case QEvent::MouseMove:
    {
        if(!pressed)
            break;
        posCursor=QCursor::pos()-posCursor;
        this->move(this->pos()+posCursor);
        posCursor=QCursor::pos();
    }
        break;
    case QEvent::MouseButtonRelease:
    {
        pressed=false;
    }
        break;
    }

    return QFrame::event(event);
}
