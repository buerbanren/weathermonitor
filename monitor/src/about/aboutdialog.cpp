#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent):
    QDialog(parent)
{
    this->setFixedSize(460,200);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->hide();

    // 主布局，垂直布局
    pvlayoutAbout=new QVBoxLayout(this);
    pvlayoutAbout->setContentsMargins(0,0,0,0);
    pvlayoutAbout->setSpacing(0);
    this->setLayout(pvlayoutAbout);

    // 标题栏布局，水平布局
    pwidgetTop=new QWidget(this);
    pwidgetTop->setFixedHeight(32);

    phlayoutTop=new QHBoxLayout(pwidgetTop);
    phlayoutTop->setContentsMargins(10,0,32,0);

    plabTitle=new QLabel(this);
    plabTitle->setFixedSize(64,32);
    plabTitle->setText("关于");
    plabTitle->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    phlayoutTop->addWidget(plabTitle);

    phspacerTop=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    phlayoutTop->addItem(phspacerTop);

    pbtCloseTop=new QPushButton(this);
    pbtCloseTop->setFixedSize(32,32);
    pbtCloseTop->setStyleSheet("background-color:white;");
    phlayoutTop->addWidget(pbtCloseTop);

    pwidgetTop->setLayout(phlayoutTop);
    pvlayoutAbout->addWidget(pwidgetTop);


    labelDescrib=new QLabel(this);
    labelDescrib->setText("文本内容");
    pvlayoutAbout->addWidget(labelDescrib);


    pwidgetBottom=new QWidget(this);
    pwidgetBottom->setFixedHeight(28);

    phlayoutBottom=new QHBoxLayout(this);
    phlayoutBottom->setContentsMargins(20,0,64,0);

    phspacerBottom=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    phlayoutBottom->addItem(phspacerBottom);

    pbtCloseBottom=new QPushButton(this);
    pbtCloseBottom->setFixedSize(64,32);
    pbtCloseBottom->setStyleSheet("background-color:white;");
    connect(pbtCloseBottom,&QPushButton::clicked,[=]()
    {
        this->close();
    });
    phlayoutBottom->addWidget(pbtCloseBottom);

    pwidgetBottom->setLayout(phlayoutBottom);
    pvlayoutAbout->addWidget(pwidgetBottom);
}
