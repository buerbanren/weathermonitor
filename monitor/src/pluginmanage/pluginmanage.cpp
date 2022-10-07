#include "pluginmanage.h"
#include "../common/comdefine.h"
#include <QEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>

#ifdef WIN32
	#include <windows.h>
#endif

typedef TestInterface* (*TestFunction)();

PluginManage::PluginManage(QWidget *parent) : QFrame(parent)
{
	this->setObjectName("FramePluginManage");

    this->setStyleSheet(Common::readFileContent(":/qss/resource/qss/pluginmanage.css").data());
    this->resize(Common::tranSize(800,580));

    initUILayout(this);

    //loadPluginDLL();
}

PluginManage::~PluginManage()
{
	try {
		for (auto itinterface : vet_interface)
		{
			if (!itinterface)
				continue;
			delete itinterface;
			itinterface = nullptr;
		}

		for (auto lib : vet_loadlibrary)
		{
			if (!lib)
				continue;
			if (lib->isLoaded())
                lib->unload();
			lib->deleteLater();
		}
	}
	catch (...)
	{
		qDebug() << u8"析构错误";
	}
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

    p_vlayout->insertWidget(0, p_frameTop);

    p_pluginOperation=new QWidget(this);
    p_gridLayoutPlugin=new QGridLayout(p_pluginOperation);
    p_gridLayoutPlugin->setMargin(0);
    p_gridLayoutPlugin->setHorizontalSpacing(Common::tranWidth(60));
    p_gridLayoutPlugin->setVerticalSpacing(Common::tranHeight(32));
    p_gridLayoutPlugin->setContentsMargins(Common::tranWidth(80),Common::tranHeight(40),
                                         Common::tranWidth(80),Common::tranHeight(40));

    p_btPluginManual=new QPushButton(this);
    p_btPluginManual->setObjectName("btLoadPlugin");
    p_btPluginManual->setFixedSize(Common::tranSize(125,125));
    p_gridLayoutPlugin->addWidget(p_btPluginManual,0,0);
    connect(p_btPluginManual,&QPushButton::clicked,this, &PluginManage::addExtraLibrary);

    p_hSpacer=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Preferred);
    p_gridLayoutPlugin->addItem(p_hSpacer,0,1,1,3);

    p_vSpacer=new QSpacerItem(20,40,QSizePolicy::Preferred,QSizePolicy::Expanding);
    p_gridLayoutPlugin->addItem(p_vSpacer,1,0,2,4);

    p_pluginOperation->setLayout(p_gridLayoutPlugin);

    // 添加所有插件页面
    p_vlayout->insertWidget(1, p_pluginOperation);


    ///////////////////////////////////////////////////
    // 单个插件页面
    p_pluginInfoUI=new PluginInfo(nullptr,this);
    p_pluginInfoUI->hide();
    connect(p_pluginInfoUI,&PluginInfo::returnPluginPage,[=]()
    {
        changePluginManagePage();
    });

    map_plugintype={
            std::pair<PluginMangePage,QWidget *>(PluginMangePage::PLUGIN_ALL,p_pluginOperation),
            std::pair<PluginMangePage,QWidget *>(PluginMangePage::PLUGIN_SINGLE,p_pluginInfoUI)
        };
}

void PluginManage::loadPluginDLL()
{
    ifstream if_pluginconfig;
    if_pluginconfig.open(PLUGIN_CONFIGFILE,ios_base::in | ios_base::binary);
    if(!if_pluginconfig.is_open())
    {
        qDebug()<<"配置文件打开失败";
        return;
    }

    // 读取保存的配置信息
    while(!if_pluginconfig.eof())
    {
        PluginConfiguration plugconfig;
        int size=if_pluginconfig.readsome((char*)&plugconfig,sizeof(PluginConfiguration));
        if(size==0)
            break;
        //if_pluginconfig.seekg(size,ios_base::seekdir::_S_cur);

        if(!loadPluginDLL(plugconfig.name))
            continue;

        map_pluginConfig[plugconfig.name]=plugconfig;

    }

    if_pluginconfig.close();
}

bool PluginManage::loadPluginDLL(std::string name, bool isnew)
{

#ifndef WIN32
    HMODULE hmodule = LoadLibraryA("test.dll");

    if(!hmodule)
        QMessageBox::warning(NULL,"错误","加载失败");

	TestFunction getInstall=(TestFunction)GetProcAddress(hmodule,"getInstall");

     FreeLibrary(hmodule);
#else
    // DLL加载测试采用Qt提供的Qlibrary方式进行加载
    QLibrary *library=new QLibrary(name.data(),this);
    if(library->isLoaded())
    {
        QMessageBox::warning(NULL,u8"提示",u8"禁止重复加载");
        return false;
    }
    TestFunction getInstall=(TestFunction)library->resolve("getInstall");
#endif

    if(!getInstall)
    {
        QMessageBox::warning(nullptr,"提示","接口获取失败");
        return false;
    }

    TestInterface *testInterface=getInstall();

	if (!testInterface)
        return false;

    //存储动态库
    vet_loadlibrary.push_back(library);
    vet_interface.push_back(testInterface);

    testWidget = testInterface->getPluginWidget();
    if(!testWidget)
        return false;
    //testWidget->setStyleSheet("background-color:red;");
    testWidget->show();
    //testWidget->setFixedSize(Common::tranWidth(525), Common::tranHeight(200));

    vec_pluginBt.push_back(new QPushButton(this));

    auto bt=vec_pluginBt.at(vec_pluginBt.size()-1);

    if(isnew)
    {
        QFileInfo fileinfo(name.data());
        PluginConfiguration _plugconfigNew;
        memset(_plugconfigNew.name,0,sizeof(_plugconfigNew.name));
        strcat_s(_plugconfigNew.name,sizeof(_plugconfigNew.name),fileinfo.baseName().toStdString().data());

        sprintf_s(_plugconfigNew.version,8,"%s","1.0.0");
        _plugconfigNew.installed=1;

        map_pluginConfig[_plugconfigNew.name]=_plugconfigNew;
    }

    // 插件按钮添加并移动
    //bt->setStyleSheet(Common::readFileContent(":/qss/resource/qss/pluginmanagebt.css").data());
    bt->update();
    bt->setFixedSize(Common::tranSize(125,125));
    bt->setIconSize(Common::tranSize(90,90));
    bt->setIcon(QIcon(QPixmap::fromImage(testInterface->getPluginIcon())));
    connect(bt,&QPushButton::clicked,[=]()
    {
        changePluginManagePage(PluginMangePage::PLUGIN_SINGLE);
        stuPluginInfo info;
        testInterface->getPluginInfo(info);
        if(this->p_pluginInfoUI)
            p_pluginInfoUI->setBaseInfo(testInterface->getPluginIcon(), info.name.data(), info.version.data(), info.copyright.data(), info.description.data());
    });

    p_gridLayoutPlugin->addWidget(bt,(vec_pluginBt.size()-1)/4,(vec_pluginBt.size()-1)%4);

    // 手动添加按钮移动
    p_gridLayoutPlugin->addWidget(p_btPluginManual,vec_pluginBt.size()/4,vec_pluginBt.size()%4);

    // 水平填充移动
	p_gridLayoutPlugin->removeItem(p_hSpacer);
	if (vec_pluginBt.size() % 4 < 3)
		p_gridLayoutPlugin->addItem(p_hSpacer, ((vec_pluginBt.size() + 1) / 4), 3 - (vec_pluginBt.size() % 4), 1, 4 - ((vec_pluginBt.size() + 1) / 4));
	//else
	//	;

    // 垂直填充移动
	p_gridLayoutPlugin->removeItem(p_vSpacer);
	if (vec_pluginBt.size() / 4 < 2)
		p_gridLayoutPlugin->addItem(p_vSpacer, vec_pluginBt.size() / 4 + 1, vec_pluginBt.size() % 4, 3 - (vec_pluginBt.size() / 4 + 1), 1);
	//else
	//	;

    emit addPluginPage(testWidget);
    return true;
}

void PluginManage::addExtraLibrary()
{
    QString pluginstr;
    pluginstr=QFileDialog::getOpenFileName(this,"请选择插件","","Plugin (*.dll)");
    if(pluginstr.isEmpty())
        return;
    loadPluginDLL(pluginstr.toStdString(),true);
}

bool PluginManage::close()
{
    reflushPluginConfiguration(this->map_pluginConfig);
    return QFrame::close();
}

void PluginManage::changePluginManagePage(PluginMangePage type)
{
    foreach(auto itpage,map_plugintype)
            itpage.second->hide();

    auto itpluginwid=map_plugintype.find(type);
    if(itpluginwid==map_plugintype.end())
        return;
    p_vlayout->addWidget(map_plugintype.at(type));
    itpluginwid->second->show();

    auto ittitle=map_plugintitle.find(type);
    if(ittitle==map_plugintitle.end())
        return;
    setTitle(map_plugintitle.at(type));

    stuPluginInfo info;
    vet_interface.at(vet_interface.size()-1)->getPluginInfo(info);

}

void PluginManage::setTitle(string title)
{
    p_labPluginTitle->setText(title.data());
}

bool PluginManage::event(QEvent *event)
{
    // 窗口位置拖动
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    {
        QPoint pos=QCursor::pos();
        if(this->mapFromGlobal(pos).y()>p_frameTop->height())
            break;
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

bool PluginManage::reflushPluginConfiguration(const std::map<std::string,PluginConfiguration> _map_pluginConfig)
{
    ofstream of_plugin;
    of_plugin.open(PLUGIN_CONFIGFILE,ios::out | ios::binary);

    if(!of_plugin.is_open())
        return false;

    // 将更改过的配置重新写入到配置文件
    foreach(auto itconfig,_map_pluginConfig)
    {
        of_plugin.write((char*)&itconfig.second,sizeof(PluginConfiguration));
        writePluginConfiguration(itconfig.second);
    }

    of_plugin.close();
    return true;
}

bool PluginManage::writePluginConfiguration(PluginConfiguration pluginconfig, bool clean)
{
    return false;
}

