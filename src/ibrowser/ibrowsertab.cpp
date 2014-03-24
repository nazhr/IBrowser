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
#include "ibrowser/ibrowsertab.h"
#include "ibrowser/ibrowsersingle.h"
#include "ibrowser/ibrowserhandler.h"

// Qt
#include <QtGui/QWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QApplication>
#include <QtGui/QLineEdit>
#include <QtCore/QSize>

// cef
#include <include/cef_base.h>
#include <include/utils/resource.h>

IBrowserTab::IBrowserTab()
	:	m_parent_window(0)
{

}
IBrowserTab::~IBrowserTab(){}

bool IBrowserTab::CreateTab(QWidget *parent)
{
	try
	{
		// ibrowser and cef handler
		CefRefPtr<IBrowserHandler> handler = new IBrowserHandler();
		IBrowserSingle::Instance().setCurrentIBrowserHandler(handler.get());

		m_parent_window = parent;
		QSize		size = parent->size();

		// create sub window
		QWidget		sub_window(parent);
		// sub window setting
		sub_window.resize(size.width(), size.height());
		// edit box setting
		QLineEdit	editHWnd(&sub_window);
		editHWnd.resize(size.width(), URLBAR_HEIGHT);
		// hwnd window
		HWND		tab_hWnd = sub_window.winId();
		
		sub_window.show();
		CreateBrowser(tab_hWnd);

		parent->show();
		// cef message loop
		CefRunMessageLoop();

	}
	catch(std::exception &e)
	{
		QMessageBox qmess;
		qmess.setWindowTitle(QApplication::translate("IBrowser Tab System Error : ", 
			"IBrowser IMainWindow System Error : "));
		qmess.setText(QApplication::translate(e.what(), e.what()));
	}
	return 1;
}

void	IBrowserTab::CreateBrowser(HWND tab_hWnd)
{
	try
	{
		// crate window
		CefRefPtr<IBrowserHandler> handler = IBrowserSingle::Instance().getCurrentIBrowserHandler();
		RECT		rect_tab;
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

		CefBrowserHost::CreateBrowser(info, handler.get(), handler->GetStartupURL(), browserSettings);
		
	}
	catch(std::exception &e)
	{
		QMessageBox qmess;
		qmess.setWindowTitle(QApplication::translate("IBrowser Tab System Error : ", 
			"IBrowser IMainWindow System Error : "));
		qmess.setText(QApplication::translate(e.what(), e.what()));
	}
}

bool IBrowserTab::BrowserLoadUrl(const std::wstring &url)
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
