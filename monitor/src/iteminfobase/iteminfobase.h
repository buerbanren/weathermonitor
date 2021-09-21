#ifndef ITEMINFOBASE_H
#define ITEMINFOBASE_H

#include <QWidget>
#include <iostream>
#include <QLabel>

#include "../common/comdefine.h"

using namespace std;

class ItemInfoBase:public QWidget
{
    Q_OBJECT
public:
    ItemInfoBase(QWidget *parent=nullptr);
    virtual ~ItemInfoBase();

    virtual void setTitle(string name);
    virtual string getTitle();

    virtual void setContent(){};

    virtual void setWeatherInfo(std::string name, std::string value)=0;

	virtual void resizeEvent(QResizeEvent *event);

private:
    QLabel *label_title=nullptr;


};

#endif // ITEMINFOBASE_H
