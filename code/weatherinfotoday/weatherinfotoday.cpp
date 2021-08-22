#include "weatherinfotoday.h"

WeatherInfoToday::WeatherInfoToday(QWidget *parent)
	:ItemInfoBase(parent)
{
	gridlayoutInfoToday = new QGridLayout(this);

    setTitle(u8"今日信息");

    foreach(auto it, mapInfoToday)
    {
		string _tempType = it.second.name;
		it.second.labelType->setText(_tempType.c_str());

		_tempType = it.second.value;
		it.second.labelValue->setText(_tempType.c_str());

		short _index = it.second.index;
		auto *ptemp = it.second.labelValue;
		ptemp->setStyleSheet(QString("font:'Mictrosoft YaHei';color:white;font-size: %1px;")
			.arg(Common::tranWidth(48)));

		ptemp->setAlignment(Qt::AlignCenter);
		ptemp->setFixedHeight(Common::tranHeight(48));
		gridlayoutInfoToday->addWidget(ptemp, 2 * (_index / 4), _index % 4);

		ptemp = it.second.labelType;
		ptemp->setStyleSheet(QString("font:'Mictrosoft YaHei';color:white;font-size:%1px;")
			.arg(Common::tranHeight(16)));
		ptemp->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
		ptemp->setFixedHeight(Common::tranHeight(26));
		gridlayoutInfoToday->addWidget(ptemp, 2 * (_index / 4) + 1, _index % 4);

	}

	gridlayoutInfoToday->setVerticalSpacing(16);
	gridlayoutInfoToday->setContentsMargins({ 30,96,40,30 });

	this->setLayout(gridlayoutInfoToday);
    this->setStyleSheet("backgroud:transparent;");
}

void WeatherInfoToday::setWeatherInfo(string name, string value)
{
    auto it=mapInfoToday.find(name);
    if(it!=mapInfoToday.end())
    {
        it->second.labelValue->setText(value.data());
    }
}

void WeatherInfoToday::resizeEvent(QResizeEvent * event)
{

    foreach(auto it, mapInfoToday)
	{
		string _tempType = it.second.name;
        //it.second.labelType->setText(_tempType.c_str());

		_tempType = it.second.value;
        //it.second.labelValue->setText(_tempType.c_str());

		short _index = it.second.index;
		auto *ptemp = it.second.labelValue;
		
		ptemp->setStyleSheet(QString("font:'Mictrosoft YaHei';color:white;font-size: %1px;")
            .arg(Common::tranHeight(42)));

        ptemp->setFixedHeight(Common::tranHeight(48));

		ptemp = it.second.labelType;
		ptemp->setStyleSheet(QString("font:'Mictrosoft YaHei';color:white;font-size: %1px;")
            .arg(Common::tranHeight(18)));

		ptemp->setFixedHeight(Common::tranHeight(26));
	}

	gridlayoutInfoToday->setVerticalSpacing(Common::tranHeight(16));
	gridlayoutInfoToday->setContentsMargins({ Common::tranWidth(30),
		Common::tranHeight(96),
		Common::tranWidth(40),
		Common::tranHeight(30) });

	return ItemInfoBase::resizeEvent(event);
}
