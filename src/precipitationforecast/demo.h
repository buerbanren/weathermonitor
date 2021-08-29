#ifndef DEMO_H
#define DEMO_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QLabel>

struct HourInfo{
    int hour;
    QString strIcoPath;
    int temp;
};

class demo : public QWidget
{
    Q_OBJECT
public:
    explicit demo(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    void addHourInfo(int hour,QString type,int temp);
    void setHoursInfo(std::vector<HourInfo> data);

    void resizeEvent(QResizeEvent *event);

signals:

private:
    QPainter *painter=nullptr;

    std::vector<HourInfo> vecHoursInfo;

};

#endif // DEMO_H
