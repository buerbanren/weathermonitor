#include "dialimage.h"

DialImage::DialImage(QWidget *parent) : QWidget(parent)
{
    imgDial=new QImage;
    painter=new QPainter();
}

void DialImage::setValue(std::string name,int value)
{
    imgDial->load(":/qss/resource/qss/dialbackground.png");

    painter->begin(imgDial);
    /* 尽可能消除锯齿边缘 */
    painter->setRenderHint(QPainter::Antialiasing);
    /* 尽可能消除文本锯齿边缘 */
    painter->setRenderHint(QPainter::TextAntialiasing);
    /* 启用线性插值算法以此来平滑图片 */
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->save();

    painter->setPen(QColor(255,255,255));

    painter->setFont(QFont("Microsoft Yahei",Common::tranHeight(132)));
    painter->drawText(Common::tranWidth(125),Common::tranHeight(201),QString::fromStdString(name));


    painter->setFont(QFont("Microsoft Yahei",Common::tranHeight(172)));
    painter->drawText(Common::tranWidth(114),Common::tranHeight(118),QString::number(value));

    painter->restore();
    painter->end();
}

void DialImage::paintEvent(QPaintEvent *event)
{
    painter->begin(this);

    QRect _rect=this->rect();
    /* 尽可能消除锯齿边缘 */
    painter->setRenderHint(QPainter::Antialiasing);
    /* 尽可能消除文本锯齿边缘 */
    painter->setRenderHint(QPainter::TextAntialiasing);
    /* 启用线性插值算法以此来平滑图片 */
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->drawImage(_rect,*imgDial,imgDial->rect());

    painter->end();
    QWidget::paintEvent(event);
}

QImage* DialImage::getImage()
{
    return imgDial;
}
