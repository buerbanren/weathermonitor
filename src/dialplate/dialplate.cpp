#include "dialplate.h"

DialPlate::DialPlate(QWidget *parent) : QWidget(parent)
{
    this->resize(320,320);
}

void DialPlate::paintEvent(QPaintEvent *event)
{
    //表盘绘制
    QPainter painter;
    painter.begin(this);
    // 保存画笔
    painter.save();
    painter.setPen(QColor(0xff,0x00,0x00));



    // 恢复画笔
    painter.restore();
    painter.end();


    QWidget::paintEvent(event);
}
