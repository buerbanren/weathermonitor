#include "topinfo.h"
#include "src/common/comdefine.h"

TopInfo::TopInfo(QWidget *parent) : QWidget(parent)
{

    this->setFixedHeight(32);

    initialControl();
}

void TopInfo::resizeEvent(QResizeEvent *event)
{
    // 加载样式
    QFile file_headercss(":/qss/resource/qss/topinfo.css");
    file_headercss.open(QIODevice::OpenModeFlag::ReadOnly);
    QString css_topinfo;
    css_topinfo.append(QString(file_headercss.readAll()).arg(Common::tranHeight(32)));
    this->setStyleSheet(css_topinfo);

    labTopInfoDate->setFixedWidth(Common::tranWidth(360));

    labTopInfoAddress->setFixedWidth(Common::tranWidth(94));

    QWidget::resizeEvent(event);
}

void TopInfo::initialControl()
{
    labTopInfoDate=new QLabel(this);
    labTopInfoDate->setAlignment(Qt::AlignLeft);
    labTopInfoDate->setFixedSize(360,32);
    labTopInfoDate->setText(QDate::currentDate().toString(u8"M月d日 yyyy年 dddd"));

    spacerItemLR1=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);

    labTopInfoAddress=new QLabel(this);
    labTopInfoAddress->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	labTopInfoAddress->setFixedSize(94, 32);
	labTopInfoAddress->setText(u8"黄岛区");

    spacerItemLR2=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);

    spacerItemLR3=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);

    spacerItemLR4=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);

    hlayoutTopInfo=new QHBoxLayout(this);
    hlayoutTopInfo->setContentsMargins({0,0,0,0});
    hlayoutTopInfo->addWidget(labTopInfoDate);
    hlayoutTopInfo->addSpacerItem(spacerItemLR1);
    hlayoutTopInfo->addWidget(labTopInfoAddress);
    hlayoutTopInfo->addSpacerItem(spacerItemLR2);
    hlayoutTopInfo->addSpacerItem(spacerItemLR3);
    hlayoutTopInfo->addSpacerItem(spacerItemLR4);
}
