#ifndef TOPINFO_H
#define TOPINFO_H

#include <QWidget>
#include <QLabel>
#include <QSpacerItem>
#include <QDate>
#include <QFile>
#include <QHBoxLayout>
#include <string>

class TopInfo : public QWidget
{
    Q_OBJECT
public:
    explicit TopInfo(QWidget *parent = nullptr);

    void setCityInfo(std::string district);

    void updateTime();

protected:
    virtual void resizeEvent(QResizeEvent *event);

signals:

private:
    /*
     * 2021.7.30 jinbo
     * 初始化控件以及默认值
     * */
    void initialControl();

private:
    QLabel *labTopInfoDate=nullptr;
    QLabel *labTopInfoAddress=nullptr;
    QLabel *labTopLastTime=nullptr;

    QSpacerItem *spacerItemLR1=nullptr;
    QSpacerItem *spacerItemLR2=nullptr;
    QSpacerItem *spacerItemLR3=nullptr;
    QSpacerItem *spacerItemLR4=nullptr;
    QHBoxLayout *hlayoutTopInfo=nullptr;

};

#endif // TOPINFO_H
