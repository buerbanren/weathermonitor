#include "dialimage.h"

DialImage::DialImage(QWidget *parent) : QWidget(parent)
{
    imgDial=new QImage;
    painter=new QPainter();
}

void DialImage::setValue(std::string name,int value)
{
    imgDial->load(":/qss/resource/qss/dialbackground.png");

    //*imgDial=imgDial->scaled(Common::tranWidth(320),Common::tranHeight(320),\
                             Qt::AspectRatioMode::IgnoreAspectRatio,Qt::TransformationMode::SmoothTransformation);

    painter->begin(imgDial);
    /* 尽可能消除锯齿边缘 */
    painter->setRenderHint(QPainter::Antialiasing);
    /* 尽可能消除文本锯齿边缘 */
    painter->setRenderHint(QPainter::TextAntialiasing);
    /* 启用线性插值算法以此来平滑图片 */
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->save();

    painter->setPen(QColor(255,255,255));

    painter->setFont(QFont("Microsoft Yahei",72,20));
    painter->drawText(QRect{114,106,82,76},Qt::AlignTop | Qt::AlignHCenter, QString::number(value));


    painter->setFont(QFont("Microsoft Yahei",32));
    painter->drawText(QRect{105,200,102,36},Qt::AlignTop | Qt::AlignHCenter, QString::fromStdString(name));

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
