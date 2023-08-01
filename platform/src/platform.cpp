#include "../include/platform.h"
#include "cefwidget\simple_app.h"
#include "cefwidget\qcefwidget.h"

Platform::Platform()
{
}

int Platform::initCef()
{
	HINSTANCE hInstance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

	// Enable High-DPI support on Windows 7 or newer.
	CefEnableHighDPISupport();

	CefRefPtr<SimpleApp> app(new SimpleApp);

	// Provide CEF with command-line arguments.
	CefMainArgs main_args(hInstance);

	int exit_code = CefExecuteProcess(main_args, app.get(), nullptr);
	if (exit_code >= 0) {
		// The sub-process has completed so return here.
		return exit_code;
	}

	// Specify CEF global settings here.
	CefSettings settings;
	settings.multi_threaded_message_loop = true;
	settings.log_severity = LOGSEVERITY_DISABLE; //»’÷æ
	settings.no_sandbox = true;

	// Initialize CEF.
	bool bInit = CefInitialize(main_args, settings, app.get(), nullptr);

	return bInit;
}

void Platform::releaseCef()
{
	CefShutdown();
}

QWidget* Platform::createCefWidget()
{
	return new QCefWidget();
}
