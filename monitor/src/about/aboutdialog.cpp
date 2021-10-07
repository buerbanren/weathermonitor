#include "aboutdialog.h"
#include "../common/comdefine.h"

AboutDialog::AboutDialog(QWidget *parent):
    QDialog(parent)
{
    this->setFixedSize(460,200);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->hide();
    this->setObjectName("aboutDialog");
    this->setStyleSheet(Common::readFileContent(":/qss/resource/qss/aboutdialog.css").data());

    // 主布局，垂直布局
    pvlayoutAbout=new QVBoxLayout(this);
    pvlayoutAbout->setContentsMargins(0,0,0,0);
    pvlayoutAbout->setSpacing(0);
    this->setLayout(pvlayoutAbout);

    // 标题栏布局，水平布局
    pwidgetTop=new QWidget(this);
    pwidgetTop->setFixedHeight(32);

    phlayoutTop=new QHBoxLayout(pwidgetTop);
    phlayoutTop->setContentsMargins(10,0,10,0);
    phlayoutTop->setAlignment(Qt::AlignVCenter);

    plabTitle=new QLabel(this);
    plabTitle->setObjectName("btaboutTitle");
    plabTitle->setFixedSize(64,32);
    plabTitle->setText("关于");
    plabTitle->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    phlayoutTop->addWidget(plabTitle);

    phspacerTop=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    phlayoutTop->addItem(phspacerTop);

    pbtCloseTop=new QPushButton(this);
    pbtCloseTop->setObjectName("btCloseTop");
    pbtCloseTop->setFixedSize(24,24);
    connect(pbtCloseTop,&QPushButton::clicked, this, &AboutDialog::close);
    phlayoutTop->addWidget(pbtCloseTop);

    pwidgetTop->setLayout(phlayoutTop);
    pvlayoutAbout->addWidget(pwidgetTop);


    // 关于信息文本
    labelDescrib=new QLabel(this);
    labelDescrib->setTextFormat(Qt::RichText);
    labelDescrib->setText("<body style=\"margin-left:72px;font-family:'Microsoft YaHei';"\
                          "font-size:14px; color:white;\">\
                          <p style=\"margin:6px;\">\
                            天气监控软件（64位版）\
                          </p>\
                          <p style=\"margin:6px;\">\
                            作者：不二般人\
                          </p>\
                          <p style=\"margin:6px;\">\
                            版本：0.0.1\
                          </p>\
                          <p style=\"margin:6px;\">\
                            时间：04-28 2021\
                          </p>\
                        </body>");
    pvlayoutAbout->addWidget(labelDescrib);


    pwidgetBottom=new QWidget(this);
    pwidgetBottom->setFixedHeight(34);


    // 底部布局
    phlayoutBottom=new QHBoxLayout(this);
    phlayoutBottom->setContentsMargins(10,0,64,10);

    phspacerBottom=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    phlayoutBottom->addItem(phspacerBottom);

    pbtCloseBottom=new QPushButton(this);
    pbtCloseBottom->setObjectName("btCloseBottom");
    pbtCloseBottom->setFixedSize(64,24);
    pbtCloseBottom->setText("关闭");
    connect(pbtCloseBottom,&QPushButton::clicked, this, &AboutDialog::close);
    phlayoutBottom->addWidget(pbtCloseBottom);

    pwidgetBottom->setLayout(phlayoutBottom);
    pvlayoutAbout->addWidget(pwidgetBottom);
}
