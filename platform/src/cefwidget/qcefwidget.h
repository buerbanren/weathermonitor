#pragma once

#include <QFrame>

#include "simple_handler.h"

class QCefWidget : public QFrame
{
	Q_OBJECT

public:
	QCefWidget(QWidget *parent = Q_NULLPTR);
	~QCefWidget();

private:
	CefRefPtr<SimpleHandler> simple_handler_;
};
