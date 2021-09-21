#ifndef DIALPLATE_H
#define DIALPLATE_H

#include <QWidget>
#include <QPainter>

class DialPlate : public QWidget
{
public:
    explicit DialPlate(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

signals:

private:
    int dial_width=30;
    int dial_default_width=320;
    int dial_default_height=320;

};

#endif // DIALPLATE_H
