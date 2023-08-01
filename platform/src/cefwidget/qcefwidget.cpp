#include "qcefwidget.h"

#include "simple_app.h"

QCefWidget::QCefWidget(QWidget *parent)
	: QFrame(parent)
{
	this->resize(600, 300);
		
	QString url = "file:///G:/Programming/C++_Qt/weathermonitor/build/debug/radar.html";// "http://www.google.com";

	QRect rect = this->rect();
	RECT rectWin;
	rectWin.left = rect.left();
	rectWin.top = rect.top();
	rectWin.right = rect.right();
	rectWin.bottom = rect.bottom();

	CefWindowInfo window_info;
	window_info.SetAsChild((HWND)this->winId(), rectWin);

	// Specify CEF browser settings here.
	CefBrowserSettings browser_settings;
	simple_handler_ = CefRefPtr<SimpleHandler>(new SimpleHandler());

	CefBrowserHost::CreateBrowser(window_info, simple_handler_, 
		url.toStdString(),
		browser_settings,
		NULL);
}

QCefWidget::~QCefWidget()
{
}
