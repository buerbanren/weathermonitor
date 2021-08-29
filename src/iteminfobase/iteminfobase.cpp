#include "iteminfobase.h"

ItemInfoBase::ItemInfoBase(QWidget *parent)
    :QWidget(parent)
{
    this->setFixedSize(540,300);

    label_title=new QLabel(this);
	label_title->setStyleSheet(u8"font-size:32px;font-family:'Microsoft YaHei';color:white;");
	label_title->setAlignment(Qt::AlignTop);
    label_title->move(1,23);
	label_title->setFixedHeight(36);
	label_title->setFixedWidth(this->width());
    label_title->setText(u8"标题");

};

ItemInfoBase::~ItemInfoBase()
{

}

void ItemInfoBase::setTitle(string name)
{
    label_title->setText(name.data());
}

string ItemInfoBase::getTitle()
{
    return label_title->text().toStdString();
}

void ItemInfoBase::resizeEvent(QResizeEvent *event)
{
	label_title->setStyleSheet(QString("font-size:%1px;font-family:'Microsoft YaHei';color:white;")
		.arg(Common::tranHeight(32)));
	label_title->setFixedSize(this->width(), Common::tranHeight(38));
	QWidget::resizeEvent(event);
}
