#ifndef DIALIMAGE_H
#define DIALIMAGE_H

#include <QObject>
#include <QImage>
#include <string>
#include <QPainter>
#include <QString>
#include "code/common/comdefine.h"

class DialImage : public QWidget
{
    Q_OBJECT
public:
    explicit DialImage(QWidget *parent = nullptr);
    void setValue(std::string name,int value);
    void paintEvent(QPaintEvent *event);
    QImage* getImage();

signals:

private:
    QImage *imgDial=nullptr;
    QPainter *painter=nullptr;

};

#endif // DIALIMAGE_H
