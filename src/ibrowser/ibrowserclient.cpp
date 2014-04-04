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
#include "ibrowser/ibrowserclient.h"

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


	int IBrowserClient::Initialize(HWND &hWnd, std::string &url)
	{
		try
		{
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

			// init ibrowser handler
			// ibrowser and cef handler
			CefRefPtr<ibrowser::IBrowserHandler> handler = new IBrowserHandler();
			IBrowserSingle::Instance().SetCurrentIBrowserHandler(handler.get());

			// create borwser
			CreateBrowser(hWnd, url);
			
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

	void IBrowserClient::CreateBrowser(HWND &tab_hWnd, std::string &url)
	{
		try
		{
			// ibrowser and cef handler
			CefRefPtr<ibrowser::IBrowserHandler> handler = IBrowserSingle
				::Instance().GetCurrentIBrowserHandler();

			RECT		rect_tab;
			// HWND		parent_hWnd = m_parent->winId();
			::GetClientRect(tab_hWnd, &rect_tab);

			// set browser screen size 
			// set browser top pos
			rect_tab.top += URLBAR_HEIGHT;

			CefBrowserSettings browserSettings;
			CefString(&browserSettings.default_encoding) = "utf-8";
			browserSettings.file_access_from_file_urls = STATE_ENABLED;
			browserSettings.universal_access_from_file_urls = STATE_ENABLED;
			CefWindowInfo	info;
			info.SetAsChild(tab_hWnd, rect_tab);

			CefBrowserHost::CreateBrowser(info, handler.get(), url, browserSettings);

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

	void IBrowserClient::CloseBrowser()
	{
		CefRefPtr<ibrowser::IBrowserHandler>	handler = IBrowserSingle
			::Instance().GetCurrentIBrowserHandler();
		if(handler.get())
		{
			CefRefPtr<CefBrowser>				browser = handler->GetBrowser();
			if(browser.get())
			{
				browser->GetHost()->CloseBrowser(false);
			}
		}
	}

	bool IBrowserClient::BrowserLoadUrl(const std::wstring &url)
	{
		IBrowserHandler				*handler = IBrowserSingle
			::Instance().GetCurrentIBrowserHandler();
		if(!url.empty() && handler)
		{
			CefRefPtr<CefBrowser>	browser = handler->GetBrowser();
			browser->GetMainFrame()->LoadURL(url);
			return true;
		}	
		return false;
	}
}
