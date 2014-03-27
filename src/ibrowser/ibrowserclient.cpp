/****************************************************************************
 *   Copyright (C) 2014 by Jerry			                           		*
 *                                                                        	*
 *   This file is part of IBrowser.                                        	*
 *                                                                         	*
 *   IBrowser is private software.                                         	*
 *   program.  If not, see <https://github.com/jerrykk/IBrowser>.          	*
 *                                                                         	*
 *   IBrowser website: https://github.com/jerrykk/IBrowser                 	*
 ****************************************************************************/

// ibrowser
#include "ibrowser/global.h"
#include "ibrowser/ibrowserclient.h"
#include "ibrowser/ibrowsertabwidget.h"
#include "ibrowser/ibrowsersingle.h"

// Qt
#include <QtGui/QWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QApplication>
#include <QtGui/QTextEdit>

namespace ibrowser 
{
	// static member init
	HINSTANCE				IBrowserClient::m_hInstance = NULL;
	CefRefPtr<IBrowserApp>	IBrowserClient::m_cef_app(0);

	IBrowserClient::IBrowserClient()
	{

	}

	IBrowserClient::~IBrowserClient(){}


	int IBrowserClient::Initialize(IMainwindow *parent)
	{
		try
		{
			m_parent = parent;
			HINSTANCE				hInstance = (HINSTANCE)GetModuleHandle(NULL);
			
			// cef
			CefMainArgs				main_args(hInstance);
			CefRefPtr<IBrowserApp>	m_cef_app = new IBrowserApp;
			int						exit_code = CefExecuteProcess(main_args, m_cef_app.get());
			if (exit_code >= 0) 
			{
				return 0;
			}
			CefSettings				settings;

			AppGetSettings(settings);

			// create sub process
			CefString(&settings.browser_subprocess_path).FromASCII("subprocess.exe");

			// cef init
			CefInitialize(main_args, settings, m_cef_app.get());
			
			m_tabWidget = parent->tabWidget();
			m_subWidget = new IBWidget();
			m_tabWidget->addTab(m_subWidget, "page 1");
			HWND browserHWnd = m_subWidget->winId();
			CreateBrowser(browserHWnd);
			
			parent->show();
			
			// cef message loop
			CefRunMessageLoop();

			CefShutdown();
			
		}
		catch(std::exception &e)
		{
			QMessageBox qmess;
			qmess.setWindowTitle(QApplication::translate("IBrowser IMainWindow System Error : ", 
				"IBrowser IMainWindow System Error : "));
			qmess.setText(QApplication::translate(e.what(), e.what()));
			qmess.show();
		}
		return 1;
	}

	void IBrowserClient::CreateBrowser(HWND &tab_hWnd)
	{
		try
		{
			// ibrowser and cef handler
			CefRefPtr<ibrowser::IBrowserHandler> handler = new IBrowserHandler();
			IBrowserSingle::Instance().setCurrentIBrowserHandler(handler.get());

			RECT		rect_tab;
			HWND		parent_hWnd = m_parent->winId();
			::GetClientRect(parent_hWnd, &rect_tab);

			// set browser screen size 
			// set browser top pos
			rect_tab.top += URLBAR_HEIGHT;

			CefBrowserSettings browserSettings;
			CefString(&browserSettings.default_encoding) = "utf-8";
			browserSettings.file_access_from_file_urls = STATE_ENABLED;
			browserSettings.universal_access_from_file_urls = STATE_ENABLED;
			CefWindowInfo	info;
			info.SetAsChild(tab_hWnd, rect_tab);

			CefBrowserHost::CreateBrowser(info, handler.get(), handler->GetStartupURL(), browserSettings);

		}
		catch(std::exception &e)
		{
			QMessageBox qmess;
			qmess.setWindowTitle(QApplication::translate("IBrowser Tab System Error : ", 
				"IBrowser IMainWindow System Error : "));
			qmess.setText(QApplication::translate(e.what(), e.what()));
			qmess.show();
		}
	}

	bool IBrowserClient::BrowserLoadUrl(const std::wstring &url)
	{
		IBrowserHandler				*handler = IBrowserSingle::
			Instance().getCurrentIBrowserHandler();
		if(!url.empty() && handler)
		{
			CefRefPtr<CefBrowser>	browser = handler->GetBrowser();
			browser->GetMainFrame()->LoadURL(url);
			return true;
		}	
		return false;
	}
}
