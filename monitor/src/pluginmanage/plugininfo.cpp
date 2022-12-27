#include "plugininfo.h"
#include "../common/comdefine.h"
#include <QTextBrowser>
#include <QApplication>

PluginInfo::PluginInfo(CPluginInterface *testInterface, QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet(Common::readFileContent(":/qss/resource/qss/plugininfo.css").data());
    init();
}

void PluginInfo::init()
{
    vlayout_info=new QVBoxLayout(this);
    vlayout_info->setContentsMargins(Common::tranWidth(10),Common::tranWidth(10),\
                                     Common::tranWidth(10),Common::tranWidth(30));
    vlayout_info->setSpacing(0);
    this->setLayout(vlayout_info);

    // 顶部返回栏
    frame_infotop=new QWidget(this);
    frame_infotop->setFixedHeight(Common::tranHeight(32));
    hlayout_infotop=new QHBoxLayout(frame_infotop);
    hlayout_infotop->setContentsMargins(0,0,0,0);
    hlayout_infotop->setSpacing(0);

    btReturn=new QPushButton(frame_infotop);
    btReturn->setObjectName("bt_returnPluginALL");
    btReturn->setFixedSize(Common::tranWidth(32),Common::tranWidth(32));
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
    //frame_infocontent->setStyleSheet("*{border: 1px solid red;}");
    vlayout_info->addWidget(frame_infocontent);

    //  插件的布局
    vlayout_infocontent = new QVBoxLayout(this->frame_infocontent);
    vlayout_infocontent->setContentsMargins(Common::tranWidth(72), Common::tranWidth(12),\
                                            Common::tranWidth(64), Common::tranWidth(24));

    hlayout_infoBase = new QHBoxLayout();
    hlayout_infoBase->setSpacing(Common::tranWidth(48));
    hlayout_infoBase->setSizeConstraint(QLayout::SetMinimumSize);
    vlayout_infocontent->addLayout(hlayout_infoBase);
    //vlayout_infocontent->addSpacerItem(new QSpacerItem(20,40,QSizePolicy::Minimum, QSizePolicy::Expanding));

    // 插件图标
    lab_icoPlugin = new QLabel(frame_infocontent);
    lab_icoPlugin->setFixedSize(Common::tranWidth(96), Common::tranWidth(96));
    lab_icoPlugin->setAlignment(Qt::AlignCenter);
    lab_icoPlugin->setText("[ico]");
    lab_icoPlugin->setScaledContents(true);

    // 插件简要信息描述布局
    layout_baseText = new QVBoxLayout();
    layout_baseText->setSpacing(Common::tranHeight(10));

    hlayout_infoBase->addWidget(lab_icoPlugin);
    hlayout_infoBase->addLayout(layout_baseText);
    //hlayout_infoBase->addSpacerItem(new QSpacerItem(40,20,QSizePolicy::Expanding, QSizePolicy::Minimum));


    // 简要信息标签
    lab_pluginName = new QLabel(frame_infocontent);
    lab_pluginName->setObjectName("pluginTitle");
    lab_pluginName->setText("JS-CSS-HTML Formatter");
    layout_baseText->addWidget(lab_pluginName);

    lab_pluginAuthor = new QLabel(frame_infocontent);
    lab_pluginAuthor->setText("lonefy");
    layout_baseText->addWidget(lab_pluginAuthor);

    lab_pluginDescBase = new QLabel(frame_infocontent);
    lab_pluginDescBase->setWordWrap(true);
    lab_pluginDescBase->setText("Format ,prettify and beautify JS, CSS, HTML code by using shortcuts, context menu or CLI");
    layout_baseText->addWidget(lab_pluginDescBase);
    //layout_baseText->addSpacerItem(new QSpacerItem(20,40,QSizePolicy::Minimum, QSizePolicy::Expanding));


    // 子页面信息
    m_pTabInfoDesc = new QTabWidget();
    m_pTabInfoDesc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    vlayout_infocontent->addWidget(m_pTabInfoDesc);

    // 添加详细描述
    m_pTabInfoDesc->addTab(new QTextBrowser(this), "细节");
    m_pTabInfoDesc->addTab(new QTextBrowser(this), "更改日志");

    //qobject_cast<QTextBrowser*>(m_pTableInfoDesc->widget(0))->setReadOnly(false);

    connect(qApp, &QApplication::focusChanged,  this, [=](QWidget *old, QWidget *now)
    {
        if(now != m_pTabInfoDesc->widget(0))
        {
            qobject_cast<QTextBrowser*>(m_pTabInfoDesc->widget(0))->setHtml(qobject_cast<QTextBrowser*>(m_pTabInfoDesc->widget(0))->toPlainText());
        }
    });
}

void PluginInfo::setBaseInfo(QImage img, QString name, QString version, QString author, QString desc)
{
    QPixmap pixmap = QPixmap::fromImage(img);
    if(this->lab_icoPlugin)
        this->lab_icoPlugin->setPixmap(pixmap);
    if(this->lab_pluginName)
        this->lab_pluginName->setText(name);
    if(this->lab_pluginAuthor)
        this->lab_pluginAuthor->setText(version + "\t " + author);
    if(this->lab_pluginDescBase)
        this->lab_pluginDescBase->setText(desc);
}

void PluginInfo::setExtraInfo(QString detail, QString modifiedLog, std::map<QString, QString> more)
{
    qobject_cast<QTextBrowser*>(m_pTabInfoDesc->widget(0))->setHtml(detail);
    qobject_cast<QTextBrowser*>(m_pTabInfoDesc->widget(1))->setHtml(modifiedLog);

    // 删除额外数据的页面
    int nPages = this->m_pTabInfoDesc->count();
    for(int i=2;i<nPages; i++)
    {
        QWidget *page = this->m_pTabInfoDesc->widget(i);
        this->m_pTabInfoDesc->removeTab(i);
        if(page)
        {
            delete page;
            page = nullptr;
        }
    }

    // 动态添加页面
    for(const auto &itPage : more)
    {
        QTextBrowser *pageExtra = new QTextBrowser(this->m_pTabInfoDesc);
        pageExtra->setHtml(itPage.second);
        m_pTabInfoDesc->addTab(pageExtra, itPage.first);
    }

}
